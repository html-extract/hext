#include "hext/pattern/literal-test.h"


namespace hext {


literal_test::literal_test(std::string literal)
: lit(literal)
{
}

bool literal_test::test(const std::string& subject) const
{
  return this->lit.compare(subject) == 0;
}

void literal_test::print(std::ostream& out) const
{
  out << "=\"" << this->lit << "\"";
}


} // namespace hext

