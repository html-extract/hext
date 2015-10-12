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

#include "hext/ContainsTest.h"

#include <utility>


namespace hext {


ContainsTest::ContainsTest(std::string literal) noexcept
: lit_(std::move(literal))  // noexcept
{
}

bool ContainsTest::test(const char * subject) const
{
  if( !subject )
    return false;

  auto str_subject = std::string(subject);
  return str_subject.find(this->lit_) != std::string::npos;
}


} // namespace hext

