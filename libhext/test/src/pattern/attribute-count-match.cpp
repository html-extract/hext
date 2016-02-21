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

TEST(Pattern_AttributeCountMatch, Matches)
{
  {
    THtml h("<div></div>");
    EXPECT_TRUE(AttributeCountMatch(0).matches(h.first()));
  }

  {
    THtml h("<div attr='attr'></div>");
    EXPECT_TRUE(AttributeCountMatch(1).matches(h.first()));
  }

  {
    THtml h("<div attr1='attr1' attr2='attr2'></div>");
    EXPECT_TRUE(AttributeCountMatch(2).matches(h.first()));
  }
}

TEST(Pattern_AttributeCountMatch, Fails)
{
  {
    THtml h("<div></div>");
    for(unsigned int i = 1; i < 10; ++i)
      EXPECT_FALSE(AttributeCountMatch(i).matches(h.first()));
  }

  {
    THtml h("<div attr='attr'></div>");
    EXPECT_FALSE(AttributeCountMatch(0).matches(h.first()));
    for(unsigned int i = 2; i < 10; ++i)
      EXPECT_FALSE(AttributeCountMatch(i).matches(h.first()));
  }
}
