#include "hext/test/EndsWith.h"


namespace hext {
namespace test {


EndsWith::EndsWith(std::string literal)
: lit_(literal)
{
}

bool EndsWith::operator()(const char * subject) const
{
  if( !subject )
    return false;

  auto str = std::string(subject);

  if( this->lit_.size() > str.size() )
    return false;

  return std::equal(this->lit_.rbegin(), this->lit_.rend(), str.rbegin());
}


} // namespace test
} // namespace hext

