#include "hext/rule.h"
#include "hext/match-tree.h"


namespace hext {


rule::rule()
: children(),
  attributes(),
  tag_name(),
  is_direct_desc(false)
{
}

void rule::append_child(const rule& r, int level)
{
  if( level > 1 && !this->children.empty() )
  {
    this->children.back().append_child(r, level - 1);
    return;
  }

  this->children.push_back(r);
}

void rule::append_attribute(const attribute& attr)
{
  this->attributes.push_back(attr);
}

std::vector<rule>::size_type rule::children_size() const
{
  return this->children.size();
}

std::string rule::get_tag_name() const
{
  return this->tag_name;
}

void rule::set_tag_name(const std::string& name)
{
  this->tag_name = name;
}

bool rule::get_is_direct_descendant() const
{
  return this->is_direct_desc;
}

void rule::set_is_direct_descendant(bool direct_desc)
{
  this->is_direct_desc = direct_desc;
}

void rule::match(const GumboNode * node, match_tree * m) const
{
  if( !node || !m || node->type != GUMBO_NODE_ELEMENT )
    return;

  if( this->matches(node) )
  {
    m = m->append_child_and_own(this->capture(node));

    for(const auto& c : this->children)
      c.match_node_children(node, m);
  }
  else
  {
    // if this rule is a direct descendant, and it didn't match,
    // all child-rules cannot be matched either.
    if( !this->is_direct_desc )
      this->match_node_children(node, m);
  }
}

void rule::print(std::ostream& out, int indent_level) const
{
  out << ( indent_level ? std::string(indent_level * 2, ' ') : "" )
      << "<"
      << this->tag_name
      << " ";

  for(const auto& a : this->attributes)
  {
    a.print(out);
    out << " ";
  }

  out << ">\n";
  for(const auto& c : this->children)
    c.print(out, indent_level + 1);
}

std::unique_ptr<match_tree>
rule::capture(const GumboNode * node) const
{
  std::unique_ptr<match_tree> m_node = make_unique<match_tree>();
  m_node->set_rule(this);

  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return m_node;

  for(const auto& attr : this->attributes)
    if( attr.is_capture() )
      m_node->append_match(attr.capture(node));

  return m_node;
}

bool rule::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  if( !this->tag_name.empty() &&
      node->v.element.tag != gumbo_tag_enum(this->tag_name.c_str()) )
    return false;

  for(const auto& attr : this->attributes)
  {
    if( !attr.matches(node) )
      return false;
  }

  return true;
}

void rule::match_node_children(const GumboNode * node, match_tree * m) const
{
  if( !node || !m || node->type != GUMBO_NODE_ELEMENT )
    return;

  const GumboVector * node_children = &node->v.element.children;
  for(unsigned int i = 0; i < node_children->length; ++i)
  {
    this->match(
      static_cast<const GumboNode *>(node_children->data[i]),
      m
    );
  }
}


} // namespace hext

