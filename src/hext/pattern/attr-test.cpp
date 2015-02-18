#include "hext/pattern/attr-test.h"


namespace hext {


attr_test::~attr_test()
{
}

bool attr_test::test(const char * /* dummy */) const
{
  return true;
}

void attr_test::print(std::ostream& /* dummy */) const
{
}


} // namespace hext

