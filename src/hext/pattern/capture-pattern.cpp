#include "hext/pattern/capture-pattern.h"


namespace hext {


CapturePattern::CapturePattern(const std::string& result_name)
: name(result_name)
, rx(nullptr)
{
}

CapturePattern::CapturePattern(
  const std::string& result_name,
  const std::string& regex
)
: name(result_name)
, rx(regex.empty() ? nullptr : make_unique<boost::regex>(regex))
{
}

CapturePattern::~CapturePattern()
{
}

std::string CapturePattern::regex_filter(const char * str) const
{
  assert(this->rx);
  if( !this->rx )
    return str;

  boost::match_results<const char *> mr;
  if( boost::regex_search(str, str + strlen(str), mr, *(this->rx)) )
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

