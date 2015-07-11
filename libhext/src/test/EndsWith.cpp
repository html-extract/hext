#include "hext/test/EndsWith.h"

#include <algorithm>
#include <utility>


namespace hext {
namespace test {


EndsWith::EndsWith(std::string literal)
: lit_(std::move(literal))
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

