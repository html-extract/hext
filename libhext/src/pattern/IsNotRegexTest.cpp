#include "hext/pattern/IsNotRegexTest.h"


namespace hext {


IsNotRegexTest::IsNotRegexTest(const boost::regex& regex)
: rx_(regex)
{
}

bool IsNotRegexTest::test(const char * subject) const
{
  return !boost::regex_search(subject, this->rx_);
}


} // namespace hext

