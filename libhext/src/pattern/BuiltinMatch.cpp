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

bool BuiltinMatch::matches(const GumboNode * node) const
{
  if( !this->func_ )
    return false;

  std::string t = this->func_(node);
  if( this->test_ )
    return this->test_->test(t.c_str());
  else
    return true;
}


} // namespace hext

