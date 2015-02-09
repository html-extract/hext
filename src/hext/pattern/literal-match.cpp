#include "hext/pattern/literal-match.h"


namespace hext {


literal_match::literal_match(
  const std::string& attr_name,
  const std::string& attr_value
)
: attribute_match(attr_name)
, literal(attr_value)
{
}

match_result literal_match::matches(const GumboNode * node) const
{
  const GumboAttribute * g_attr = this->get_node_attr(node);
  if( g_attr && strlen(g_attr->value) == this->literal.size() )
    if( this->literal.compare(g_attr->value) == 0 )
      return match_result(true, g_attr);

  return match_result(false, nullptr);
}

void literal_match::print(std::ostream& out) const
{
  out << ' ' << this->attr << "=\"" << this->literal << '"';
}


} // namespace hext

