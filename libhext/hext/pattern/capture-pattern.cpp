#include "hext/pattern/capture-pattern.h"


namespace hext {


CapturePattern::CapturePattern(const std::string& result_name)
: name_(result_name)
, rx_()
{
}

CapturePattern::CapturePattern(
  const std::string& result_name,
  const boost::regex& regex
)
: name_(result_name)
, rx_(regex)
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
  if( boost::regex_search(str, str + strlen(str), mr, this->rx_.get()) )
  {
    // If there are no captures, return whole string (mr[0]), if there are
    // captures, then return the first one
    return mr.size() > 1 ? mr[1] : mr[0];
  }
  else
  {
    return "";
  }
}


} // namespace hext

