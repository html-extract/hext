#include "hext/test/ContainsWord.h"


namespace hext {
namespace test {


ContainsWord::ContainsWord(std::string literal)
: lit_(std::move(literal))
{
}

bool ContainsWord::operator()(const char * subject) const
{
  if( !subject )
    return false;

  return hext::ContainsWord(std::string(subject), this->lit_);
}


} // namespace test
} // namespace hext

