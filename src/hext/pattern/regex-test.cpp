#include "hext/pattern/regex-test.h"


namespace hext {


RegexTest::RegexTest(const std::string& regex)
: rx_(regex)
{
}

bool RegexTest::test(const char * subject) const
{
  return boost::regex_search(subject, this->rx_);
}

void RegexTest::print(std::ostream& out) const
{
  out << "=/" << this->rx_.str() << "/";
}


} // namespace hext

