#include "hext/pattern/regex-test.h"


namespace hext {


RegexText::RegexText(const std::string& regex)
: rx(regex)
{
}

bool RegexText::test(const char * subject) const
{
  return boost::regex_search(subject, this->rx);
}

void RegexText::print(std::ostream& out) const
{
  out << "=/" << this->rx.str() << "/";
}


} // namespace hext

