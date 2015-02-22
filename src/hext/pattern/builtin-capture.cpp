#include "hext/pattern/builtin-capture.h"


namespace hext {


BuiltinCapture::BuiltinCapture(
  const std::string& result_name,
  bi::BuiltinFuncPtr f,
  const std::string& regex
)
: CapturePattern(result_name, regex)
, func_(f)
{
}

MatchTree::NameValuePair
BuiltinCapture::capture(const GumboNode * node) const
{
  assert(this->func_);
  if( !this->func_ )
    return MatchTree::NameValuePair(this->name_, "");

  std::string val = this->func_(node);

  if( this->rx_ )
  {
    return MatchTree::NameValuePair(
      this->name_,
      this->regex_filter(val.c_str())
    );
  }
  else
  {
    return MatchTree::NameValuePair(this->name_, val);
  }
}

void BuiltinCapture::print(std::ostream& out) const
{
  out << " @"
      << bi::get_name_by_builtin(this->func_)
      << "={"
      << this->name_;
  if( this->rx_ )
    out << '/' << this->rx_->str() << '/';
  out << '}';
}


} // namespace hext

