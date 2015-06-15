#include "hext/pattern/BuiltinCapture.h"


namespace hext {


BuiltinCapture::BuiltinCapture(
  const std::string& result_name,
  BuiltinFuncPtr func,
  const boost::optional<boost::regex>& regex
)
: CapturePattern(result_name, regex)
, func_(func)
{
}

ResultPair BuiltinCapture::capture(const GumboNode * node) const
{
  assert(this->func_);
  if( !this->func_ )
    return ResultPair(this->name_, "");

  std::string val = this->func_(node);

  if( this->rx_ )
  {
    return ResultPair(
      this->name_,
      this->regex_filter(val.c_str())
    );
  }
  else
  {
    return ResultPair(this->name_, val);
  }
}


} // namespace hext

