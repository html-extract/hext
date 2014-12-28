#include "hext/rule.h"


namespace hext {


rule::rule()
: children(),
  attributes(),
  tag_name()
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

void rule::append_attribute(attribute attr)
{
  this->attributes.push_back(attr);
}

void rule::set_tag_name(std::string name)
{
  this->tag_name = name;
}

void rule::match_recursively(const GumboNode * node, match_tree * m) const
{
  typedef std::vector<rule>::const_iterator r_child_iter;

  if( node == nullptr )
    return;

  if( m == nullptr )
    return;

  if( node->type != GUMBO_NODE_ELEMENT )
    return;

  if( this->matches(node) )
  {
    m = m->append_child_and_own(this->capture(node));

    // if we do not have any child-rules left, we have found a complete
    // match.

    if( this->children.empty() )
    {
      m->set_is_complete(true);
    }
    else
    {
      for(r_child_iter it = this->children.begin(); it != this->children.end(); ++it)
      {
        it->match_node_children(node, m);
      }
    }
  }
  else
  {
    this->match_node_children(node, m);
  }
}

void rule::match_node_children(const GumboNode * node, match_tree * m) const
{
  if( node == nullptr )
    return;

  if( m == nullptr )
    return;

  if( node->type != GUMBO_NODE_ELEMENT )
    return;

  const GumboVector * node_children = &node->v.element.children;
  for(unsigned int i = 0; i < node_children->length; ++i)
  {
    this->match_recursively(
      static_cast<const GumboNode *>(node_children->data[i]),
      m
    );
  }
}

bool rule::matches(const GumboNode * node) const
{
  typedef std::vector<attribute>::const_iterator r_attr_iter;

  if( node == nullptr )
    return false;

  if( node->type != GUMBO_NODE_ELEMENT )
    return false;

  if( !this->tag_name.empty() &&
      node->v.element.tag != gumbo_tag_enum(this->tag_name.c_str()) )
    return false;

  for(r_attr_iter it = this->attributes.begin(); it != this->attributes.end(); ++it)
  {
    std::string attr_name = it->get_name();

    GumboAttribute * g_attr =
      gumbo_get_attribute(&node->v.element.attributes, attr_name.c_str());
    if( !g_attr && !it->is_builtin() )
      return false;

    std::string attr_value = it->get_value();
    if( !it->is_capture() && !attr_value.empty() )
    {
      if( attr_value.compare(g_attr->value) != 0 )
        return false;
    }
  }

  return true;
}

std::unique_ptr<match_tree>
rule::capture(const GumboNode * node) const
{
  typedef std::vector<attribute>::const_iterator r_attr_iter;

  std::unique_ptr<match_tree> m_node = make_unique<match_tree>();

  if( node == nullptr )
    return m_node;

  if( node->type != GUMBO_NODE_ELEMENT )
    return m_node;

  for(r_attr_iter it = this->attributes.begin(); it != this->attributes.end(); ++it)
  {
    if( it->is_capture() )
    {
      m_node->append_match(
        it->capture(node)
      );
    }
  }

  return m_node;
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
  {
    c.print(out, indent_level + 1);
  }
}


} // namespace hext

