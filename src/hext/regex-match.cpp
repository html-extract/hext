#include "hext/regex-match.h"


namespace hext {


regex_match::regex_match(
  const std::string& attr_name,
  const std::string& regex
)
: attribute_match(attr_name)
, rx(regex)
{
}

match_result regex_match::matches(const GumboNode * node) const
{
  const GumboAttribute * g_attr = this->get_node_attr(node);
  if( g_attr && boost::regex_search(g_attr->value, this->rx) )
    return match_result(true, g_attr);
  else
    return match_result(false, nullptr);
}

void regex_match::print(std::ostream& out) const
{
  out << ' ' << this->attr << "=\"/" << this->rx.str() << "/\"";
}


} // namespace hext

