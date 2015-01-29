#include "hext/match-pattern.h"


namespace hext {


match_pattern::match_pattern(const std::string& attr_name)
: attr(attr_name)
{
}

match_result match_pattern::matches(const GumboNode * node) const
{
  const GumboAttribute * g_attr = this->get_node_attr(node);
  return match_result(g_attr != nullptr, g_attr);
}

void match_pattern::print(std::ostream& out) const
{
  out << this->attr << " ";
}

match_pattern::~match_pattern()
{
}

const GumboAttribute *
match_pattern::get_node_attr(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return nullptr;

  return gumbo_get_attribute(&node->v.element.attributes, this->attr.c_str());
}


} // namespace hext

