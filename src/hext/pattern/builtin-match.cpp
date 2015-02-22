#include "hext/pattern/builtin-match.h"


namespace hext {


BuiltinMatch::BuiltinMatch(
  bi::BuiltinFuncPtr f,
  std::unique_ptr<AttrTest> attribute_test
)
: MatchPattern(std::move(attribute_test))
, func(f)
{
}

MatchResult BuiltinMatch::matches(const GumboNode * node) const
{
  if( !this->func )
    return MatchResult(false, nullptr);

  std::string t = this->func(node);
  if( this->test )
    return MatchResult(this->test->test(t.c_str()), nullptr);
  else
    return MatchResult(true, nullptr);
}

void BuiltinMatch::print(std::ostream& out) const
{
  out << " @"
      << bi::get_name_by_builtin(this->func);
  if( this->test )
    this->test->print(out);
}


} // namespace hext

