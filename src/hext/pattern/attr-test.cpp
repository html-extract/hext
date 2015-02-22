#include "hext/pattern/attr-test.h"


namespace hext {


AttrTest::~AttrTest()
{
}

bool AttrTest::test(const char * /* dummy */) const
{
  return true;
}

void AttrTest::print(std::ostream& /* dummy */) const
{
}


} // namespace hext

