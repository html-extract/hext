#include "hext/builtin-capture.h"


namespace hext {


builtin_capture::builtin_capture(
  const std::string& result_name,
  bi::builtin_func_ptr f,
  const std::string& regex
)
: capture_pattern(result_name, regex)
, func(f)
{
}

match_tree::name_value_pair
builtin_capture::capture(const GumboNode * node) const
{
  assert(this->func);
  if( !this->func )
    return match_tree::name_value_pair(this->name, "");

  std::string val = this->func(node);

  if( this->rx )
  {
    return match_tree::name_value_pair(
      this->name,
      this->regex_filter(val.c_str())
    );
  }
  else
  {
    return match_tree::name_value_pair(this->name, val);
  }
}

void builtin_capture::print(std::ostream& out) const
{
  out << '@'
      << bi::get_name_by_builtin(this->func)
      << "=\"{"
      << this->name;
  if( this->rx )
    out << "/" << this->rx->str() << "/";
  out << "}\" ";
}


} // namespace hext

