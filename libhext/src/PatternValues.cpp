// Copyright 2015-2017 Thomas Trapp
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

#include "PatternValues.h"

#include <cassert>


namespace hext {


PatternValues::PatternValues()
: nth(0, 0)
, builtin(nullptr)
, attr_name()
, literal_value()
, cap_var()
, pipe(nullptr)
, regex()
, test(nullptr)
, trait(nullptr)
, negate(nullptr)
, regex_flag(boost::regex::perl)
, optional(false)
{
}

void PatternValues::reset()
{
  this->builtin = nullptr;
  this->optional = false;
  this->attr_name = "";
  this->literal_value = "";
  this->cap_var = "";
  this->regex_flag = boost::regex::perl;
  this->regex = std::optional<boost::regex>();
  assert(this->pipe.get() == nullptr);
  this->pipe = nullptr;
  this->nth = {0, 0};
  assert(this->test.get() == nullptr);
  this->test = nullptr;
  assert(this->trait.get() == nullptr);
  this->trait = nullptr;
  assert(this->negate.get() == nullptr);
  this->negate = nullptr;
}


} // namespace hext

