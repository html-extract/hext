// Copyright 2015 Thomas Trapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

