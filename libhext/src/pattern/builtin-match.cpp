#include "hext/pattern/builtin-match.h"


namespace hext {


BuiltinMatch::BuiltinMatch(
  BuiltinFuncPtr f,
  std::unique_ptr<ValueTest> value_test
)
: MatchPattern(std::move(value_test))
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
      << GetNameByBuiltin(this->func_);
  if( this->test_ )
    this->test_->print(out);
}


} // namespace hext

