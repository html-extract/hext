#include "hext/pattern/ContainsTest.h"


namespace hext {


ContainsTest::ContainsTest(std::string literal)
: lit_(literal)
{
}

bool ContainsTest::test(const char * subject) const
{
  if( !subject )
    return false;

  auto str_subject = std::string(subject);
  return str_subject.find(this->lit_) != std::string::npos;
}


} // namespace hext

