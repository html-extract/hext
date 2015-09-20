#include "hext/TrimPipe.h"

#include <boost/algorithm/string.hpp>


namespace hext {


TrimPipe::TrimPipe(std::string trim_any_of)
: trim_any_of_(std::move(trim_any_of))
{
}

std::string TrimPipe::transform(std::string str) const
{
  boost::trim_if(str, boost::is_any_of(this->trim_any_of_));
  return str;
}


} // namespace hext

