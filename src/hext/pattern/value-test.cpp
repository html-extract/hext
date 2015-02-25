#include "hext/pattern/value-test.h"


namespace hext {


ValueTest::~ValueTest()
{
}

bool ValueTest::test(const char * /* dummy */) const
{
  return true;
}

void ValueTest::print(std::ostream& /* dummy */) const
{
}


} // namespace hext

