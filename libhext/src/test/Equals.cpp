#include "hext/test/Equals.h"


namespace hext {
namespace test {


Equals::Equals(std::string literal)
: lit_(literal)
{
}

bool Equals::operator()(const char * subject) const
{
  return subject && this->lit_.compare(subject) == 0;
}


} // namespace test
} // namespace hext

