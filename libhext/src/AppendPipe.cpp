#include "hext/AppendPipe.h"


namespace hext {


AppendPipe::AppendPipe(std::string suffix)
: suffix_(std::move(suffix))
{
}

std::string AppendPipe::transform(std::string str) const
{
  str.append(this->suffix_);
  return str;
}


} // namespace hext

