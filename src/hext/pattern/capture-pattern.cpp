#include "hext/pattern/capture-pattern.h"


namespace hext {


CapturePattern::CapturePattern(const std::string& result_name)
: name_(result_name)
, rx_(nullptr)
{
}

CapturePattern::CapturePattern(
  const std::string& result_name,
  const std::string& regex
)
: name_(result_name)
, rx_(regex.empty() ? nullptr : MakeUnique<boost::regex>(regex))
{
}

CapturePattern::~CapturePattern()
{
}

std::string CapturePattern::regex_filter(const char * str) const
{
  assert(this->rx_);
  if( !this->rx_ )
    return str;

  boost::match_results<const char *> mr;
  if( boost::regex_search(str, str + strlen(str), mr, *(this->rx_)) )
  {
    // If there are no captures, return whole string (mr[0]), if there are
    // captures, then return the first one
    if( mr.size() > 1 )
      return mr[1];
    else
      return mr[0];
  }
  else
  {
    return "";
  }
}


} // namespace hext

