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

bool literal_match::matches(const GumboNode * node) const
{
  const GumboAttribute * g_attr = this->get_node_attr(node);
  return g_attr && this->literal.compare(g_attr->value);
}

void literal_match::print(std::ostream& out) const
{
  out << this->attr << "=\"" << this->literal << "\" ";
}


} // namespace hext

