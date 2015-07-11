#include "hext/test/Contains.h"

#include <utility>


namespace hext {
namespace test {


Contains::Contains(std::string literal)
: lit_(std::move(literal))
{
}

bool Contains::operator()(const char * subject) const
{
  if( !subject )
    return false;

  auto str_subject = std::string(subject);
  return str_subject.find(this->lit_) != std::string::npos;
}


} // namespace test
} // namespace hext

