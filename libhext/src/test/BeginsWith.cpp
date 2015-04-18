#include "hext/test/BeginsWith.h"


namespace hext {
namespace test {


BeginsWith::BeginsWith(std::string literal)
: lit_(literal)
{
}

bool BeginsWith::test(const char * subject) const
{
  if( !subject )
    return false;

  std::size_t length = std::strlen(subject);
  return 
    this->lit_.size() <= length &&
    this->lit_.compare(0, this->lit_.size(), subject, this->lit_.size()) == 0;
}


} // namespace test
} // namespace hext

