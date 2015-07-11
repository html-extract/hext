#include "hext/pattern/BuiltinMatch.h"

#include <cassert>
#include <string>
#include <utility>


namespace hext {


BuiltinMatch::BuiltinMatch(
  BuiltinFuncPtr func,
  std::unique_ptr<ValueTest> value_test
)
: func_(func)
, test_(std::move(value_test))
{
}

bool BuiltinMatch::matches(const GumboNode * node) const
{
  assert(this->func_);
  if( !this->func_ || !this->test_ )
    return false;

  std::string str = this->func_(node);
  return (*this->test_)(str.c_str());
}


} // namespace hext

