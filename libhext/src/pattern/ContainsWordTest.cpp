#include "hext/pattern/ContainsWordTest.h"


namespace hext {


ContainsWordTest::ContainsWordTest(std::string literal)
: lit_(literal)
{
}

bool ContainsWordTest::test(const char * subject) const
{
  if( !subject || this->lit_.empty() )
    return false;

  auto str_subject = std::string(subject);
  auto begin = str_subject.find(this->lit_);

  if( begin == std::string::npos )
    return false;

  std::string::size_type end = begin + this->lit_.size();

  // Check if either at start of string or prefixed with space.
  bool start_is_bound = ( begin == 0 || str_subject[begin-1] == ' ' );
  // Check if either at end of string or suffixed with space.
  bool end_is_bound = ( end == str_subject.size() || str_subject[end] == ' ' );

  return start_is_bound && end_is_bound;
}


} // namespace hext

