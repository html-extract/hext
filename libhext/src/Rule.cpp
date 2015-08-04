#include "hext/Rule.h"

#include "MatchContext.h"
#include "NodeUtil.h"


namespace hext {


Rule::Rule(HtmlTag tag,
           bool    optional,
           bool    any_descendant)
: first_child_(nullptr)
, next_(nullptr)
, matches_()
, captures_()
, tag_(tag)
, is_optional_(optional)
, is_any_descendant_(any_descendant)
{
}

Rule::~Rule() = default;
Rule::Rule(Rule&&) = default;

Rule::Rule(const Rule& other)
: first_child_(nullptr)
, next_(nullptr)
, matches_()
, captures_()
, tag_(other.tag_)
, is_optional_(other.is_optional_)
, is_any_descendant_(other.is_any_descendant_)
{
  if( other.first_child_ )
    this->first_child_ = std::make_unique<Rule>(*(other.first_child_));

  if( other.next_ )
    this->next_ = std::make_unique<Rule>(*(other.next_));

  this->matches_.reserve(other.matches_.size());
  for(const auto& m : other.matches_)
    this->matches_.emplace_back(m ? m->clone() : nullptr);

  this->captures_.reserve(other.captures_.size());
  for(const auto& c : other.captures_)
    this->captures_.emplace_back(c ? c->clone() : nullptr);
}

Rule& Rule::operator=(Rule&&) = default;

Rule& Rule::operator=(const Rule& other)
{
  using std::swap;
  Rule tmp(other);
  swap(*this, tmp);
  return *this;
}

const Rule * Rule::child() const
{
  return this->first_child_.get();
}

const Rule * Rule::next() const
{
  return this->next_.get();
}

Rule& Rule::append(Rule rule, std::size_t insert_at_depth)
{
  this->append_child_at_depth(std::move(rule), insert_at_depth);
  return *this;
}

Rule& Rule::append_match(std::unique_ptr<Match> match)
{
  this->matches_.push_back(std::move(match));
  return *this;
}

Rule& Rule::append_capture(std::unique_ptr<Capture> cap)
{
  this->captures_.push_back(std::move(cap));
  return *this;
}

HtmlTag Rule::get_tag() const noexcept
{
  return this->tag_;
}

Rule& Rule::set_tag(HtmlTag tag) noexcept
{
  this->tag_ = tag;
  return *this;
}

bool Rule::is_optional() const noexcept
{
  return this->is_optional_;
}

Rule& Rule::set_optional(bool optional) noexcept
{
  this->is_optional_ = optional;
  return *this;
}

bool Rule::is_any_descendant() const noexcept
{
  return this->is_any_descendant_;
}

Rule& Rule::set_any_descendant(bool any_descendant) noexcept
{
  this->is_any_descendant_ = any_descendant;
  return *this;
}

bool Rule::matches(const GumboNode * node) const
{
  if( !node )
    return false;

  if( this->tag_ != HtmlTag::ANY )
    if( node->type != GUMBO_NODE_ELEMENT ||
        node->v.element.tag != static_cast<GumboTag>(this->tag_) )
      return false;

  for( const auto& match : this->matches_ )
    if( !match->matches(node) )
      return false;

  return true;
}

std::vector<ResultPair> Rule::capture(const GumboNode * node) const
{
  if( !node )
    return {};

  std::vector<ResultPair> values;
  values.reserve(this->captures_.size());
  for( const auto& cap : this->captures_ )
    if( auto pair = cap->capture(node) )
      values.push_back(*pair);

  return values;
}

hext::Result Rule::extract(const GumboNode * node) const
{
  CaptureNodes capture_nodes;

  bool matched_anything =
      this->extract_capture_nodes(node,
                                  /* insert_sentinel: */ true,
                                  capture_nodes);

  hext::Result result;
  if( matched_anything )
  {
    ResultMap map;
    for( auto pair : capture_nodes )
    {
      // std::pair<nullptr, nullptr> acts as a sentinel to separate capture
      // groups
      if( !pair.first )
      {
        assert(!pair.second);
        if( !map.empty() )
        {
          result.push_back(std::move(map));
          map.clear();
        }
      }
      else
      {
        if( (pair.first)->captures_.size() )
        {
          auto values = (pair.first)->capture(pair.second);
          if( values.size() )
            map.insert(values.begin(), values.end());
        }
      }
    }
  }
  else
  {
    assert(capture_nodes.empty());
  }

  return result;
}

bool Rule::extract_capture_nodes(const GumboNode * node,
                                 bool              insert_sentinel,
                                 CaptureNodes&     result) const
{
  assert(node);
  if( !node )
    return false;

  bool matched_anything = false;
  CaptureNodes pairs;
  MatchContext mc(this, node);

  while( auto mg = mc.match_next() )
  {
    pairs.clear();
    bool save_group = true;
    for( auto match_pair : *mg )
    {
      const Rule * r = match_pair.first;
      const GumboNode * n = match_pair.second;

      const GumboNode * node_first_child = nullptr;
      if( n->type == GUMBO_NODE_ELEMENT && n->v.element.children.length )
      {
        node_first_child = static_cast<const GumboNode *>(
            n->v.element.children.data[0]);
      }

      if( !r->first_child_ ||
          r->first_child_->extract_capture_nodes(node_first_child,
                                                 /* insert_sentinel: */ false,
                                                 pairs) )
      {
        if( (match_pair.first)->captures_.size() )
          pairs.push_back(match_pair);
      }
      else
      {
        // jump to next match group (also: scared of the goto police).
        save_group = false;
        break;
      }
    }

    if( save_group )
    {
      result.reserve(result.size() + pairs.size());
      std::move(pairs.begin(), pairs.end(), std::back_inserter(result));
      pairs.clear();
      if( insert_sentinel )
        result.push_back(std::make_pair<const Rule *, const GumboNode *>(
            nullptr,
            nullptr));
      matched_anything = true;
    }
  }

  if( this->is_any_descendant_ )
  {
    const GumboNode * next_node = node;
    do
    {
      if( next_node->type == GUMBO_NODE_ELEMENT &&
          next_node->v.element.children.length )
      {
        auto next_node_first_child = static_cast<const GumboNode *>(
            next_node->v.element.children.data[0]);

        if( this->extract_capture_nodes(next_node_first_child,
                                        insert_sentinel,
                                        pairs) )
        {
          result.reserve(result.size() + pairs.size());
          std::move(pairs.begin(), pairs.end(), std::back_inserter(result));
          pairs.clear();
          if( insert_sentinel )
            result.push_back(
                std::make_pair<const Rule *,
                               const GumboNode *>(nullptr, nullptr));
          std::move(pairs.begin(), pairs.end(), std::back_inserter(result));
          matched_anything = true;
        }
      }
    }
    while( (next_node = NextNode(next_node)) );
  }

  // return whether this rule was satisfied: either something must have been
  // matched, or this rule must be optional.
  return matched_anything || this->is_optional_;
}

void Rule::append_child_at_depth(Rule        rule,
                                 std::size_t insert_at_depth)
{
  Rule * insert_at = this;
  while( insert_at->next_ )
    insert_at = insert_at->next_.get();

  if( insert_at_depth == 0 )
    insert_at->next_ = std::make_unique<Rule>(std::move(rule));
  else
    if( insert_at->first_child_ )
      insert_at->first_child_
          ->append_child_at_depth(std::move(rule), insert_at_depth - 1);
    else
      insert_at->first_child_ = std::make_unique<Rule>(std::move(rule));

  return;
}


} // namespace hext

