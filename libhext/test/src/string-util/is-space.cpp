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

#include "helper/common.h"
using namespace hext;

#include <limits>
#include <vector>

TEST(StringUtil_IsSpace, DidntChangeBehaviour)
{
  char c_min = std::numeric_limits<char>::min();
  char c_max = std::numeric_limits<char>::max();
  std::vector<char> allowed_spaces = {' ','\t','\n','\f','\r'};

  for(int i = c_min; i <= c_max; ++i)
  {
    bool is_space = IsSpace(static_cast<char>(i));
    bool expected = std::find(
      allowed_spaces.begin(),
      allowed_spaces.end(),
      static_cast<char>(i)
    ) != allowed_spaces.end();
    EXPECT_EQ(is_space, expected);
  }
}

