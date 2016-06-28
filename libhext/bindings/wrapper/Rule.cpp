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

#include "wrapper/Rule.h"
#include "hext/ParseHext.h"


Rule::Rule(const std::string& hext)
: rule_(hext::ParseHext(hext.c_str(), hext.size()))
{
}

std::vector<std::multimap<std::string, std::string>>
Rule::extract(const Html& html) const
{
  return this->rule_.extract(html.root());
}

