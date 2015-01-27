#include "hext/capture-pattern.h"


namespace hext {


capture_pattern::capture_pattern(
  const std::string& result_name,
  const std::string& regex
)
: name(result_name)
, rx(regex.empty() ? nullptr : new boost::regex(regex))
{
}

capture_pattern::~capture_pattern()
{
}

std::string capture_pattern::regex_filter(const char * str) const
{
  assert(this->rx);
  boost::match_results<const char *> mr;

  if( boost::regex_match(str, str + strlen(str), mr, *(this->rx)) )
  {
    assert(mr.size() > 1);
    return mr[1];
  }
  else
  {
    return "";
  }
}


} // namespace hext

