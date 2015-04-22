#include "hext/Rule.h"
#include "hext/ResultTree.h"


namespace hext {


Rule::Rule(
  GumboTag tag,
  bool is_optional,
  bool is_any_descendant,
  bool is_path,
  std::vector<std::unique_ptr<MatchPattern>>&& match_patterns,
  std::vector<std::unique_ptr<CapturePattern>>&& capture_patterns
)
: children_()
, match_patterns_(std::move(match_patterns))
, capture_patterns_(std::move(capture_patterns))
, gumbo_tag_(tag)
, is_optional_(is_optional)
, is_any_descendant_(is_any_descendant)
, is_path_(is_path)
{
}

void Rule::append_child(Rule&& r, int level)
{
  if( level > 1 && !this->children_.empty() )
  {
    this->children_.back().append_child(std::move(r), level - 1);
    return;
  }

  this->children_.push_back(std::move(r));
}

const std::vector<Rule>& Rule::children() const
{
  return this->children_;
}

bool Rule::optional() const
{
  return this->is_optional_;
}

std::unique_ptr<ResultTree> Rule::extract(const GumboNode * node) const
{
  auto rt = MakeUnique<ResultTree>(nullptr);
  this->extract_recursive(node, rt.get());
  return std::move(rt);
}

void Rule::extract_recursive(const GumboNode * node, ResultTree * rt) const
{
  if( !rt || !node )
    return;

  if( this->matches(node) )
  {
    // Although we have a match, this may not be the html-node that the user
    // is searching for, so we have to keep matching.
    if( this->is_any_descendant_ )
      this->extract_node_children(node, rt);

    if( !this->is_path_ )
    {
      std::vector<ResultPair> values = this->capture(node);
      rt = rt->create_branch(this, values);
    }

    for(const auto& c : this->children_)
      c.extract_node_children(node, rt);
  }
  else
  {
    // Only continue matching if this Rule matches any descendant.
    if( this->is_any_descendant_ )
      this->extract_node_children(node, rt);
  }
}

bool Rule::matches(const GumboNode * node) const
{
  if( !node )
    return false;

  if( this->gumbo_tag_ != GUMBO_TAG_UNKNOWN )
    if( node->type != GUMBO_NODE_ELEMENT ||
        node->v.element.tag != this->gumbo_tag_ )
      return false;

  for(const auto& pattern : this->match_patterns_)
    if( !pattern->matches(node) )
      return false;

  return true;
}

std::vector<ResultPair> Rule::capture(const GumboNode * node) const
{
  if( !node )
    return std::vector<ResultPair>();

  std::vector<ResultPair> values;
  values.reserve(this->capture_patterns_.size());
  for(const auto& pattern : this->capture_patterns_ )
    values.push_back(pattern->capture(node));

  return values;
}

void Rule::extract_node_children(const GumboNode * node, ResultTree * rt) const
{
  if( !rt || !node || node->type != GUMBO_NODE_ELEMENT )
    return;

  const GumboVector * node_children = &node->v.element.children;
  for(unsigned int i = 0; i < node_children->length; ++i)
  {
    this->extract_recursive(
      static_cast<const GumboNode *>(node_children->data[i]),
      rt
    );
  }
}


} // namespace hext

