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


TEST(Pattern_OnlyChildMatch, Matches)
{
  {
    THtml h("<div><b></b><b></b></div>");
    OnlyChildMatch m;
    EXPECT_TRUE(m.matches(h.first()));
  }

  {
    THtml h("<b></b><div></div>");
    OnlyChildMatch m(OnlyChildMatch::OfType);
    EXPECT_TRUE(m.matches(h.body_child(1)));
    EXPECT_TRUE(m.matches(h.body_child(2)));
  }
}

TEST(Pattern_OnlyChildMatch, Fails)
{
  {
    THtml h("<b></b><b></b>");
    OnlyChildMatch m;
    EXPECT_FALSE(m.matches(h.first()));
  }

  {
    THtml h("<b></b><b></b>");
    OnlyChildMatch m(OnlyChildMatch::OfType);
    EXPECT_FALSE(m.matches(h.body_child(1)));
    EXPECT_FALSE(m.matches(h.body_child(2)));
  }
}

