#include "hext/pattern/BuiltinMatch.h"


namespace hext {


BuiltinMatch::BuiltinMatch(
  BuiltinFuncPtr func,
  std::unique_ptr<ValueTest> value_test
)
: ValueMatch(std::move(value_test))
, func_(func)
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


} // namespace hext

