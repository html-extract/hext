#include "hext/pattern/builtin-capture.h"


namespace hext {


BuiltinCapture::BuiltinCapture(
  const std::string& result_name,
  BuiltinFuncPtr f
)
: CapturePattern(result_name)
, func_(f)
{
}

BuiltinCapture::BuiltinCapture(
  const std::string& result_name,
  BuiltinFuncPtr f,
  const boost::regex& regex
)
: CapturePattern(result_name, regex)
, func_(f)
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

void BuiltinCapture::print(std::ostream& out) const
{
  out << " @"
      << GetNameByBuiltin(this->func_)
      << "={"
      << this->name_;
  if( this->rx_ )
    out << '/' << this->rx_->str() << '/';
  out << '}';
}


} // namespace hext

