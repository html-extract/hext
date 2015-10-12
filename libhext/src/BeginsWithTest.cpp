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

#include "hext/BeginsWithTest.h"

#include <cstring>
#include <cstddef>
#include <utility>


namespace hext {


BeginsWithTest::BeginsWithTest(std::string literal) noexcept
: lit_(std::move(literal))  // noexcept
{
}

bool BeginsWithTest::test(const char * subject) const
{
  if( !subject )
    return false;

  std::size_t length = std::strlen(subject);
  return
      this->lit_.size() <= length &&
      this->lit_.compare(0, this->lit_.size(), subject, this->lit_.size()) == 0;
}


} // namespace hext

