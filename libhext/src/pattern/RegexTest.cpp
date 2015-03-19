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


} // namespace hext

