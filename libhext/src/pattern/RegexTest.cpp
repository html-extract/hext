#include "hext/pattern/RegexTest.h"


namespace hext {


RegexTest::RegexTest(const boost::regex& regex)
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

