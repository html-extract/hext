// Copyright 2015, 2016 Thomas Trapp
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

#include "hext/FunctionValueMatch.h"

#include <algorithm>
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

FunctionValueMatch::FunctionValueMatch(const FunctionValueMatch& other)
: func_(other.func_)
, test_(other.test_ ? other.test_->clone() : nullptr)
{
}

FunctionValueMatch&
FunctionValueMatch::operator=(const FunctionValueMatch& other)
{
  using std::swap;
  FunctionValueMatch tmp(other);
  swap(*this, tmp);
  return *this;
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

