#include "hext/regex-match.h"


namespace hext {


regex_match::regex_match(
  const std::string& attr_name,
  const std::string& regex
)
: match_pattern(attr_name)
, rx(regex)
{
}

bool regex_match::matches(const GumboNode * node) const
{
  const GumboAttribute * g_attr = this->get_node_attr(node);
  return g_attr && boost::regex_search(g_attr->value, this->rx);
}

void regex_match::print(std::ostream& out) const
{
  out << this->attr << "=\"/" << this->rx.str() << "/\" ";
}


} // namespace hext


