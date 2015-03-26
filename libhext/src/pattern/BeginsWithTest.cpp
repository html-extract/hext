#include "hext/pattern/BeginsWithTest.h"


namespace hext {


BeginsWithTest::BeginsWithTest(std::string literal)
: lit_(literal)
{
}

bool BeginsWithTest::test(const char * subject) const
{
  if( !subject )
    return false;

  std::size_t length = std::strlen(subject);
  return 
    this->lit_.size() <= length &&
    this->lit_.compare(0, this->lit_.size(), subject, this->lit_.size()) == 0;
}


} // namespace hext

