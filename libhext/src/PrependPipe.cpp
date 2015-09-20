#include "hext/PrependPipe.h"


namespace hext {


PrependPipe::PrependPipe(std::string prefix)
: prefix_(std::move(prefix))
{
}

std::string PrependPipe::transform(std::string str) const
{
  str.insert(0, this->prefix_);
  return str;
}


} // namespace hext

