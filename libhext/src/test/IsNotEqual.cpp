#include "hext/test/IsNotEqual.h"


namespace hext {
namespace test {


IsNotEqual::IsNotEqual(std::string literal)
: lit_(literal)
{
}

bool IsNotEqual::operator()(const char * subject) const
{
  return subject && this->lit_.compare(subject) != 0;
}


} // namespace test
} // namespace hext

