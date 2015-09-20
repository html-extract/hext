#include "hext/RegexReplacePipe.h"


namespace hext {


RegexReplacePipe::RegexReplacePipe(boost::regex regex, std::string str)
: regex_(std::move(regex))
, replace_(std::move(str))
{
}

std::string RegexReplacePipe::transform(std::string str) const
{
  return boost::regex_replace(str, this->regex_, this->replace_);
}


} // namespace hext

