#include "hext/Rule.h"

#include "MatchContext.h"


namespace hext {


struct Rule::Impl
{
  Impl(HtmlTag tag, bool optional, bool path)
  : children_()
  , matches_()
  , captures_()
  , tag_(tag)
  , is_optional_(optional)
  , is_path_(path)
  {
  }

  bool matches(const GumboNode * node) const
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

  std::vector<ResultPair> capture(const GumboNode * node) const
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

  /// Match this rule recursively against node and its child nodes.
  void extract_this_rule(const GumboNode * node, ResultTree * rt) const
  {
    if( !node || !rt )
      return;

    if( node->type != GUMBO_NODE_ELEMENT )
      return;

    if( this->matches(node) )
    {
      if( !this->is_path_ )
      {
        auto branch = rt->create_child();
        if( !this->extract_children(node, branch) )
        {
          rt->delete_child(branch);
        }
        else
        {
          branch->set_values(std::move(this->capture(node)));
        }
      }
      else
      {
        this->extract_children(node, rt);
      }
    }

    const GumboVector& node_children = node->v.element.children;
    for(unsigned int i = 0; i < node_children.length; ++i)
    {
      auto child_node = static_cast<const GumboNode *>(node_children.data[i]);
      this->extract_this_rule(child_node, rt);
    }
  }

  /// Apply this rule's children to the children of `node`, store results in
  /// `rt`.
  bool extract_children(const GumboNode * node, ResultTree * rt) const
  {
    if( !node || !rt )
      return false;

    if( this->children_.empty() )
      return true;

    if( node->type != GUMBO_NODE_ELEMENT )
      return false;

    int match_count = 0;
    MatchContext mc(this->children_.cbegin(),
                    this->children_.cend(),
                    node->v.element.children);
    while( auto grouped_match = mc.match_next() )
    {
      ++match_count;
      auto branch = rt->create_child();

      for( const auto& match_pair : *grouped_match )
      {
        const Rule * child_rule = match_pair.first;
        const GumboNode * child_node = match_pair.second;
        assert(child_rule && child_node);
        auto& cimpl = child_rule->impl_;

        ResultTree * child_rt = rt;
        if( !cimpl->is_path_ )
          child_rt = branch->create_child();

        if( !cimpl->extract_children(child_node, child_rt) )
        {
          if( cimpl->is_optional_ && !cimpl->is_path_ )
          {
            branch->delete_child(child_rt);
          }
          else
          {
            --match_count;
            if( !cimpl->is_path_ )
              rt->delete_child(branch);
            break;
          }
        }
        else if( !cimpl->is_path_ )
        {
          child_rt->set_values(child_rule->capture(child_node));
        }
      }
    }

    return match_count > 0 || this->all_children_are_optional();
  }

  void append_child_at_depth(Rule&& r, std::size_t insert_at_depth)
  {
    if( insert_at_depth > 0 && this->children_.size() )
    {
      this->children_.back().impl_
          ->append_child_at_depth(std::move(r), insert_at_depth - 1);
      return;
    }

    this->children_.push_back(std::move(r));
  }

  /// Return true if all immediate children are optional.
  bool all_children_are_optional() const noexcept
  {
    for( const auto& r : this->children_ )
      if( !r.impl_->is_optional_ )
        return false;

    return true;
  }

  std::vector<Rule> children_;
  std::vector<std::unique_ptr<Match>> matches_;
  std::vector<std::unique_ptr<Capture>> captures_;
  HtmlTag tag_;
  bool is_optional_;
  bool is_path_;
};


Rule::Rule(HtmlTag tag,
           bool    optional,
           bool    path)
: impl_(std::make_unique<Rule::Impl>(tag, optional, path))
{
}

Rule::Rule(Rule&&) noexcept = default;
Rule& Rule::operator=(Rule&&) noexcept = default;
Rule::~Rule() noexcept = default;

Rule& Rule::take_child(Rule&& r, std::size_t insert_at_depth)
{
  this->impl_->append_child_at_depth(std::move(r), insert_at_depth);
  return *this;
}

Rule& Rule::take_match(std::unique_ptr<Match>&& match)
{
  this->impl_->matches_.push_back(std::move(match));
  return *this;
}

Rule& Rule::take_capture(std::unique_ptr<Capture>&& cap)
{
  this->impl_->captures_.push_back(std::move(cap));
  return *this;
}

HtmlTag Rule::get_tag() const noexcept
{
  return this->impl_->tag_;
}

Rule& Rule::set_tag(HtmlTag tag) noexcept
{
  this->impl_->tag_ = tag;
  return *this;
}

bool Rule::is_optional() const noexcept
{
  return this->impl_->is_optional_;
}

Rule& Rule::set_optional(bool optional) noexcept
{
  this->impl_->is_optional_ = optional;
  return *this;
}

bool Rule::is_path() const noexcept
{
  return this->impl_->is_path_;
}

Rule& Rule::set_path(bool path) noexcept
{
  this->impl_->is_path_ = path;
  return *this;
}

std::unique_ptr<ResultTree> Rule::extract(const GumboNode * node) const
{
  auto rt = std::make_unique<ResultTree>();
  this->impl_->extract_this_rule(node, rt.get());
  return std::move(rt);
}

bool Rule::matches(const GumboNode * node) const
{
  return this->impl_->matches(node);
}

std::vector<ResultPair> Rule::capture(const GumboNode * node) const
{
  return this->impl_->capture(node);
}


} // namespace hext

