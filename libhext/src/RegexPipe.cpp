#include "hext/RegexPipe.h"


namespace hext {


RegexPipe::RegexPipe(boost::regex regex)
: regex_(std::move(regex))
{
}

std::string RegexPipe::transform(std::string str) const
{
  boost::match_results<const char *> mr;
  if( boost::regex_search(str.c_str(), mr, this->regex_) )
  {
    // If there are no parentheses contained within the regex, return whole
    // regex capture (mr[0]), if there are, then return the first one.
    return ( mr.size() > 1 ? mr[1] : mr[0] );
  }

  return "";
}


} // namespace hext

