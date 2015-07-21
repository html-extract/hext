#include "hext/RegexTest.h"

#include <utility>


namespace hext {


RegexTest::RegexTest(boost::regex regex)
: rx_(std::move(regex))  // not noexcept
{
}

bool RegexTest::test(const char * subject) const
{
  if( !subject )
    return false;

  return boost::regex_search(subject, this->rx_);
}


} // namespace hext

