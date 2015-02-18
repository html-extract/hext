#include "hext/pattern/regex-test.h"


namespace hext {


regex_test::regex_test(const std::string& regex)
: rx(regex)
{
}

bool regex_test::test(const std::string& subject) const
{
  return boost::regex_search(subject, this->rx);
}

void regex_test::print(std::ostream& out) const
{
  out << "=/" << this->rx.str() << "/";
}


} // namespace hext

