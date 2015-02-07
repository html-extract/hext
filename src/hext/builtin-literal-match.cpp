#include "hext/builtin-literal-match.h"


namespace hext {


builtin_literal_match::builtin_literal_match(
  bi::builtin_func_ptr f,
  const std::string& attr_value
)
: func(f)
, value(attr_value)
{
}

match_result builtin_literal_match::matches(const GumboNode * node) const
{
  std::string t = this->func(node);
  if( t.size() == this->value.size() && t.compare(this->value) == 0 )
    return match_result(true, nullptr);
  else
    return match_result(false, nullptr);
}

void builtin_literal_match::print(std::ostream& out) const
{
  out << " @"
      << bi::get_name_by_builtin(this->func)
      << "=\""
      << this->value
      << '"';
}


} // namespace hext

