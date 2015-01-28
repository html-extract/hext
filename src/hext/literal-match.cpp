#include "hext/literal-match.h"


namespace hext {


literal_match::literal_match(
  const std::string& attr_name,
  const std::string& attr_value
)
: match_pattern(attr_name)
, literal(attr_value)
{
}

const GumboAttribute * literal_match::matches(const GumboNode * node) const
{
  const GumboAttribute * g_attr = this->get_node_attr(node);
  if( g_attr && this->literal.compare(g_attr->value) == 0 )
    return g_attr;
  else
    return nullptr;
}

void literal_match::print(std::ostream& out) const
{
  out << this->attr << "=\"" << this->literal << "\" ";
}


} // namespace hext

