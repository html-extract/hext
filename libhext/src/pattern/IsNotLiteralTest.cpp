#include "hext/pattern/IsNotLiteralTest.h"


namespace hext {


IsNotLiteralTest::IsNotLiteralTest(std::string literal)
: lit_(literal)
{
}

bool IsNotLiteralTest::test(const char * subject) const
{
  return subject && this->lit_.compare(subject) != 0;
}


} // namespace hext

