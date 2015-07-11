#include "hext/RegexTest.h"

#include <utility>


namespace hext {


RegexTest::RegexTest(boost::regex regex)
: rx_(std::move(regex))
{
}

bool RegexTest::operator()(const char * subject) const
{
  if( !subject )
    return false;

  return boost::regex_search(subject, this->rx_);
}


} // namespace hext

