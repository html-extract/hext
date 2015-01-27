#include "hext/match-pattern.h"


namespace hext {


match_pattern::match_pattern(const std::string& attr_name)
: attr(attr_name)
{
}

bool match_pattern::matches(const GumboNode * node) const
{
  return this->get_node_attr(node) != nullptr;
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

