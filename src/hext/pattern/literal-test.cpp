#include "hext/pattern/literal-test.h"


namespace hext {


LiteralTest::LiteralTest(std::string literal)
: lit(literal)
{
}

bool LiteralTest::test(const char * subject) const
{
  return subject && this->lit.compare(subject) == 0;
}

void LiteralTest::print(std::ostream& out) const
{
  out << "=\"" << this->lit << "\"";
}


} // namespace hext

