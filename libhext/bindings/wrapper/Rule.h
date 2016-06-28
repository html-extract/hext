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

#ifndef WRAPPER_RULE_H_INCLUDED
#define WRAPPER_RULE_H_INCLUDED

#include "wrapper/Html.h"
#include "hext/Rule.h"
#include "hext/SyntaxError.h"

#include <map>
#include <string>
#include <vector>


class Rule
{
public:
  explicit Rule(const std::string& hext);

  std::vector<std::multimap<std::string, std::string>>
  extract(const Html& html) const;

private:
  hext::Rule rule_;
};


#endif // WRAPPER_RULE_H_INCLUDED

