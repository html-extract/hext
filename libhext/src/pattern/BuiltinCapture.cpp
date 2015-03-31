#include "hext/pattern/BuiltinCapture.h"


namespace hext {


BuiltinCapture::BuiltinCapture(
  const std::string& result_name,
  BuiltinFuncPtr func
)
: CapturePattern(result_name)
, func_(func)
{
}

BuiltinCapture::BuiltinCapture(
  const std::string& result_name,
  BuiltinFuncPtr func,
  const boost::regex& regex
)
: CapturePattern(result_name, regex)
, func_(func)
{
}

ResultTree::NameValuePair
BuiltinCapture::capture(const GumboNode * node) const
{
  assert(this->func_);
  if( !this->func_ )
    return ResultTree::NameValuePair(this->name_, "");

  std::string val = this->func_(node);

  if( this->rx_ )
  {
    return ResultTree::NameValuePair(
      this->name_,
      this->regex_filter(val.c_str())
    );
  }
  else
  {
    return ResultTree::NameValuePair(this->name_, val);
  }
}


} // namespace hext

