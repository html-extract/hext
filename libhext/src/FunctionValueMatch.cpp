#include "hext/FunctionValueMatch.h"

#include <cassert>
#include <string>
#include <utility>


namespace hext {


FunctionValueMatch::FunctionValueMatch(CaptureFunction            func,
                                       std::unique_ptr<ValueTest> value_test)
: func_(std::move(func))        // not noexcept (std::function move assignment)
, test_(std::move(value_test))  // noexcept
{
}

bool FunctionValueMatch::matches(const GumboNode * node) const
{
  assert(this->func_);
  if( !this->func_ || !this->test_ )
    return false;

  auto str = this->func_(node);
  return this->test_->test(str.c_str());
}


} // namespace hext

