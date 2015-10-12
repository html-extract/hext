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

#include "hext/EqualsTest.h"

#include <utility>


namespace hext {


EqualsTest::EqualsTest(std::string literal) noexcept
: lit_(std::move(literal))  // noexcept
{
}

bool EqualsTest::test(const char * subject) const
{
  return subject && this->lit_.compare(subject) == 0;
}


} // namespace hext

