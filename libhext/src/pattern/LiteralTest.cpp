#include "hext/pattern/LiteralTest.h"


namespace hext {


LiteralTest::LiteralTest(std::string literal)
: lit_(literal)
{
}

bool LiteralTest::test(const char * subject) const
{
  return subject && this->lit_.compare(subject) == 0;
}


} // namespace hext

