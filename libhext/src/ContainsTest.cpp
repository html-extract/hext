#include "hext/ContainsTest.h"

#include <utility>


namespace hext {


ContainsTest::ContainsTest(std::string literal)
: lit_(std::move(literal))
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

