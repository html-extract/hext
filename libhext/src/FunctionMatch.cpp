#include "hext/FunctionMatch.h"

#include <cassert>
#include <utility>


namespace hext {


FunctionMatch::FunctionMatch(MatchFunction func)
: func_(std::move(func))  // not noexcept (std::function move assignment)
{
}

bool FunctionMatch::matches(const GumboNode * node) const
{
  assert(this->func_);
  if( !this->func_ )
    return false;

  return this->func_(node);
}


} // namespace hext

