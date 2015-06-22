#include "hext/pattern/CapturePattern.h"


namespace hext {


CapturePattern::CapturePattern(
  std::string result_name,
  boost::optional<boost::regex> regex
)
: name_(std::move(result_name))
, rx_(std::move(regex))
{
}

CapturePattern::~CapturePattern()
{
}

std::string CapturePattern::regex_filter(const char * str) const
{
  if( !this->rx_ )
    return str;

  boost::match_results<const char *> mr;
  if( boost::regex_search(str, str + std::strlen(str), mr, this->rx_.get()) )
  {
    // If there are no parentheses contained within the regex, return whole
    // regex capture (mr[0]), if there are, then return the first one.
    return mr.size() > 1 ? mr[1] : mr[0];
  }
  else
  {
    return "";
  }
}


} // namespace hext

