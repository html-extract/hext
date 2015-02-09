#include "hext/pattern/attribute-match.h"


namespace hext {


attribute_match::attribute_match(const std::string& attr_name)
: attr(attr_name)
{
}

attribute_match::~attribute_match()
{
}

match_result attribute_match::matches(const GumboNode * node) const
{
  const GumboAttribute * g_attr = this->get_node_attr(node);
  return match_result(g_attr != nullptr, g_attr);
}

void attribute_match::print(std::ostream& out) const
{
  out << " " << this->attr;
}

const GumboAttribute *
attribute_match::get_node_attr(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return nullptr;

  return gumbo_get_attribute(&node->v.element.attributes, this->attr.c_str());
}


} // namespace hext

