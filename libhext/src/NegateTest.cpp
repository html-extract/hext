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

#include "hext/NegateTest.h"

#include <algorithm>
#include <utility>


namespace hext {


NegateTest::NegateTest(std::unique_ptr<ValueTest> value_test) noexcept
: test_(std::move(value_test))  // noexcept
{
}

NegateTest::NegateTest(const NegateTest& other)
: test_(other.test_ ? other.test_->clone() : nullptr)
{
}

NegateTest& NegateTest::operator=(const NegateTest& other)
{
  using std::swap;
  NegateTest tmp(other);
  swap(*this, tmp);
  return *this;
}

bool NegateTest::test(const char * subject) const
{
  if( this->test_ )
    return !this->test_->test(subject);
  else
    return subject == nullptr;
}


} // namespace hext

