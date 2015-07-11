#include "hext/EqualsTest.h"

#include <utility>


namespace hext {


EqualsTest::EqualsTest(std::string literal)
: lit_(std::move(literal))
{
}

bool EqualsTest::operator()(const char * subject) const
{
  return subject && this->lit_.compare(subject) == 0;
}


} // namespace hext

