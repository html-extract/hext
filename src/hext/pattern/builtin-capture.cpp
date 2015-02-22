#include "hext/pattern/builtin-capture.h"


namespace hext {


BuiltinCapture::BuiltinCapture(
  const std::string& result_name,
  bi::BuiltinFuncPtr f,
  const std::string& regex
)
: CapturePattern(result_name, regex)
, func(f)
{
}

MatchTree::NameValuePair
BuiltinCapture::capture(const GumboNode * node) const
{
  assert(this->func);
  if( !this->func )
    return MatchTree::NameValuePair(this->name, "");

  std::string val = this->func(node);

  if( this->rx )
  {
    return MatchTree::NameValuePair(
      this->name,
      this->regex_filter(val.c_str())
    );
  }
  else
  {
    return MatchTree::NameValuePair(this->name, val);
  }
}

void BuiltinCapture::print(std::ostream& out) const
{
  out << " @"
      << bi::get_name_by_builtin(this->func)
      << "={"
      << this->name;
  if( this->rx )
    out << '/' << this->rx->str() << '/';
  out << '}';
}


} // namespace hext

