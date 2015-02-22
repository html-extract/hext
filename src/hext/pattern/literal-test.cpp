#include "hext/pattern/literal-test.h"


namespace hext {


LiteralTest::LiteralTest(std::string literal)
: lit_(literal)
{
}

bool LiteralTest::test(const char * subject) const
{
  return subject && this->lit_.compare(subject) == 0;
}

void LiteralTest::print(std::ostream& out) const
{
  out << "=\"" << this->lit_ << "\"";
}


} // namespace hext

