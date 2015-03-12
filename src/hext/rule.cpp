#include "hext/rule.h"
#include "hext/result-tree.h"


namespace hext {


Rule::Rule(
  GumboTag tag,
  bool is_optional,
  int nth_child,
  bool closed,
  RulePatterns&& r_patterns
)
: children_()
, patterns_(std::move(r_patterns))
, gumbo_tag_(tag)
, is_optional_(is_optional)
, nth_child_(nth_child)
, is_closed_(closed)
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

GumboTag Rule::gumbo_tag() const
{
  return this->gumbo_tag_;
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
    this->extract_node_children(node, rt);

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
    // if this rule is a direct descendant, and it didn't match,
    // all child-rules cannot be matched either.
    if( this->nth_child_ == -1 )
      this->extract_node_children(node, rt);
  }
}

void Rule::print(
  std::ostream& out,
  int indent_level
) const
{
  out << ( indent_level ? std::string(indent_level * 2, ' ') : "" )
      << "<"
      << ( this->is_optional_ ? "?" : "" )
      << ( this->nth_child_ == 0 ? "!" : "" );

  if( this->nth_child_ > 0 )
    out << this->nth_child_;

  if( this->gumbo_tag_ != GUMBO_TAG_UNKNOWN )
    out << gumbo_normalized_tagname(this->gumbo_tag_);

  this->patterns_.print(out);

  if( this->is_closed_ )
    out << ">";

  out << "\n";
  for(const auto& c : this->children_)
    c.print(out, indent_level + 1);
}

bool Rule::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  if( this->gumbo_tag_ != GUMBO_TAG_UNKNOWN )
    if( node->v.element.tag != this->gumbo_tag_ )
      return false;

  if( this->nth_child_ > 0 )
  {
    unsigned int pos = GetNodePositionWithinParent(node);
    if( pos != static_cast<unsigned int>(this->nth_child_) )
      return false;
  }

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

