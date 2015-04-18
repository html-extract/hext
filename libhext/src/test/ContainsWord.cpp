#include "hext/test/ContainsWord.h"


namespace hext {
namespace test {


ContainsWord::ContainsWord(std::string literal)
: lit_(literal)
{
}

bool ContainsWord::test(const char * subject) const
{
  if( !subject || this->lit_.empty() )
    return false;

  auto str_subject = std::string(subject);

  std::string::size_type begin = 0;
  while( (begin = str_subject.find(this->lit_, begin)) != std::string::npos )
  {
    std::string::size_type end = begin + this->lit_.size();

    // Check if either at start of string or prefixed with space.
    bool start_is_bound = ( begin == 0 || str_subject[begin-1] == ' ' );

    // Check if either at end of string or suffixed with space.
    bool end_is_bound = ( end == str_subject.size() || str_subject[end] == ' ' );

    if( start_is_bound && end_is_bound )
      return true;

    begin = end;
  }

  return false;
}


} // namespace test
} // namespace hext

