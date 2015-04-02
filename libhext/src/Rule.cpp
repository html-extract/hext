#include "hext/Rule.h"
#include "hext/ResultTree.h"


namespace hext {


Rule::Rule(
  GumboTag tag,
  bool is_optional,
  bool is_any_descendant,
  bool is_path,
  bool is_closed,
  RulePatterns&& r_patterns
)
: children_()
, patterns_(std::move(r_patterns))
, gumbo_tag_(tag)
, is_optional_(is_optional)
, is_any_descendant_(is_any_descendant)
, is_path_(is_path)
, is_closed_(is_closed)
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

void Rule::extract(const GumboNode * node, ResultTree * rt) const
{
  if( !rt || !node || node->type != GUMBO_NODE_ELEMENT )
    return;

  if( this->matches(node) )
  {
    // Although we have a match, this may not be the html-node that the user
    // is searching for, so we have to keep matching.
    if( this->is_any_descendant_ )
      this->extract_node_children(node, rt);

    if( !this->is_path_ )
    {
      std::vector<ResultTree::NameValuePair> values
        = this->patterns_.capture(node);
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
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  if( this->gumbo_tag_ != GUMBO_TAG_UNKNOWN )
    if( node->v.element.tag != this->gumbo_tag_ )
      return false;

  if( this->is_closed_ )
    return this->patterns_.matches_all_attributes(node);
  else
    return this->patterns_.matches(node);
}

void Rule::extract_node_children(const GumboNode * node, ResultTree * rt) const
{
  if( !rt || !node || node->type != GUMBO_NODE_ELEMENT )
    return;

  const GumboVector * node_children = &node->v.element.children;
  for(unsigned int i = 0; i < node_children->length; ++i)
  {
    this->extract(
      static_cast<const GumboNode *>(node_children->data[i]),
      rt
    );
  }
}


} // namespace hext

