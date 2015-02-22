#include "hext/pattern/builtin-match.h"


namespace hext {


BuiltinMatch::BuiltinMatch(
  bi::BuiltinFuncPtr f,
  std::unique_ptr<AttrTest> attribute_test
)
: MatchPattern(std::move(attribute_test))
, func_(f)
{
}

MatchResult BuiltinMatch::matches(const GumboNode * node) const
{
  if( !this->func_ )
    return MatchResult(false, nullptr);

  std::string t = this->func_(node);
  if( this->test_ )
    return MatchResult(this->test_->test(t.c_str()), nullptr);
  else
    return MatchResult(true, nullptr);
}

void BuiltinMatch::print(std::ostream& out) const
{
  out << " @"
      << bi::get_name_by_builtin(this->func_);
  if( this->test_ )
    this->test_->print(out);
}


} // namespace hext

