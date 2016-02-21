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


TEST(Pattern_EqualsTest, Succeeds)
{
  {
    EqualsTest t("word");
    EXPECT_TRUE(t.test("word"));
  }

  {
    EqualsTest t("");
    EXPECT_TRUE(t.test(""));
  }
}

TEST(Pattern_EqualsTest, Fails)
{
  {
    EqualsTest t("word");
    EXPECT_FALSE(t.test("words"));
    EXPECT_FALSE(t.test("sword"));
    EXPECT_FALSE(t.test("wrd"));
    EXPECT_FALSE(t.test("wor"));
  }

  {
    EqualsTest t("");
    EXPECT_FALSE(t.test("w"));
    EXPECT_FALSE(t.test("word"));
  }
}

