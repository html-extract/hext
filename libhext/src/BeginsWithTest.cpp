#include "hext/BeginsWithTest.h"

#include <cstring>
#include <utility>


namespace hext {


BeginsWithTest::BeginsWithTest(std::string literal)
: lit_(std::move(literal))
{
}

bool BeginsWithTest::operator()(const char * subject) const
{
  if( !subject )
    return false;

  std::size_t length = std::strlen(subject);
  return
    this->lit_.size() <= length &&
    this->lit_.compare(0, this->lit_.size(), subject, this->lit_.size()) == 0;
}


} // namespace hext

