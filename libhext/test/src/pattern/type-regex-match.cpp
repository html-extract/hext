// Copyright 2024 Thomas Trapp
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


TEST(Pattern_TypeRegexMatch, Matches)
{
  {
    THtml h("<div></div>");
    EXPECT_TRUE(TypeRegexMatch(boost::regex("div")).matches(h.first()));
  }

  {
    THtml h(
      "<div></div>"      // 1
      "<a></a>"          // 2
      "<bdiv></bdiv>"    // 3
      "<c></c>"          // 4
      "<dc></dc>"        // 5
      "<divc></divc>");  // 6
    auto div_or_c = boost::regex("^(div)$|^(c)$");
    EXPECT_TRUE( TypeRegexMatch(div_or_c).matches(h.body_child(1)));
    EXPECT_FALSE(TypeRegexMatch(div_or_c).matches(h.body_child(2)));
    EXPECT_FALSE(TypeRegexMatch(div_or_c).matches(h.body_child(3)));
    EXPECT_TRUE( TypeRegexMatch(div_or_c).matches(h.body_child(4)));
    EXPECT_FALSE(TypeRegexMatch(div_or_c).matches(h.body_child(5)));
    EXPECT_FALSE(TypeRegexMatch(div_or_c).matches(h.body_child(6)));
    auto bdiv = boost::regex("bdiv");
    EXPECT_FALSE(TypeRegexMatch(bdiv).matches(h.body_child(1)));
    EXPECT_FALSE(TypeRegexMatch(bdiv).matches(h.body_child(2)));
    EXPECT_TRUE( TypeRegexMatch(bdiv).matches(h.body_child(3)));
    EXPECT_FALSE(TypeRegexMatch(bdiv).matches(h.body_child(4)));
    EXPECT_FALSE(TypeRegexMatch(bdiv).matches(h.body_child(5)));
    EXPECT_FALSE(TypeRegexMatch(bdiv).matches(h.body_child(6)));
  }
}

