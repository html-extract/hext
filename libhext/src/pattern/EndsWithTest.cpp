#include "hext/pattern/EndsWithTest.h"


namespace hext {


EndsWithTest::EndsWithTest(std::string literal)
: lit_(literal)
{
}

bool EndsWithTest::test(const char * subject) const
{
  if( !subject )
    return false;

  auto str = std::string(subject);

  if( this->lit_.size() > str.size() )
    return false;

  return std::equal(this->lit_.rbegin(), this->lit_.rend(), str.rbegin());
}


} // namespace hext

