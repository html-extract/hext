#include "hext/pattern/builtin-match.h"


namespace hext {


builtin_match::builtin_match(
  bi::builtin_func_ptr f,
  std::unique_ptr<attr_test> attribute_test
)
: match_pattern(std::move(attribute_test))
, func(f)
{
}

match_result builtin_match::matches(const GumboNode * node) const
{
  if( !this->func )
    return match_result(false, nullptr);

  std::string t = this->func(node);
  if( this->test )
    return match_result(this->test->test(t.c_str()), nullptr);
  else
    return match_result(true, nullptr);
}

void builtin_match::print(std::ostream& out) const
{
  out << " @"
      << bi::get_name_by_builtin(this->func);
  if( this->test )
    this->test->print(out);
}


} // namespace hext

