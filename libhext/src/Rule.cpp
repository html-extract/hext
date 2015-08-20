#include "hext/Rule.h"

#include "RuleMatching.h"


namespace hext {


Rule::Rule(HtmlTag tag,
           bool    optional)
: first_child_(nullptr)
, next_(nullptr)
, matches_()
, captures_()
, tag_(tag)
, is_optional_(optional)
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

Rule& Rule::append_child(Rule new_child)
{
  if( this->first_child_ )
    this->first_child_->append_next(std::move(new_child));
  else
    this->first_child_ = std::make_unique<Rule>(std::move(new_child));

  return *this;
}

Rule& Rule::append_next(Rule sibling)
{
  Rule * target = this;
  while( target->next_ )
    target = target->next_.get();

  target->next_ = std::make_unique<Rule>(std::move(sibling));
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

hext::Result Rule::extract(const Html& html) const
{
  return this->extract(html.root());
}

hext::Result Rule::extract(const GumboNode * node) const
{
  std::vector<MatchingNodes> mn;
  SaveMatchingNodesRecursive(this, node, mn);

  hext::Result result;
  for( const auto& group : mn )
  {
    ResultMap map;
    for( const auto& pair : group )
    {
      if( (pair.first)->captures_.size() )
      {
        auto values = (pair.first)->capture(pair.second);
        if( values.size() )
          map.insert(values.begin(), values.end());
      }
    }

    if( !map.empty() )
    {
      result.push_back(std::move(map));
    }
  }

  return result;
}


} // namespace hext

