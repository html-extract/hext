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

#include <string>
#include <utility>
#include <vector>


TEST(StringUtil_TrimAndCollapseWs, EmptyString)
{
  EXPECT_EQ(TrimAndCollapseWs(""), "");
  EXPECT_EQ(TrimAndCollapseWs(" "), "");
  EXPECT_EQ(TrimAndCollapseWs("  "), "");
  EXPECT_EQ(TrimAndCollapseWs("   "), "");
}

TEST(StringUtil_TrimAndCollapseWs, AlreadyTrimmed)
{
  EXPECT_EQ(TrimAndCollapseWs("a"), "a");
}

TEST(StringUtil_TrimAndCollapseWs, Trim)
{
  EXPECT_EQ(TrimAndCollapseWs(" \n left"), "left");
  EXPECT_EQ(TrimAndCollapseWs("right \n "), "right");
  EXPECT_EQ(TrimAndCollapseWs("   \t leftright \n "), "leftright");
}

TEST(StringUtil_TrimAndCollapseWs, Collapse)
{
  std::vector<std::pair<std::string, std::string>> checks = {
    {"   \t l  e ftr    ig \n\t\r ht \n ", "l e ftr ig ht"},
    {"left           right", "left right"},
    {"left           right ", "left right"},
    {"left\nright", "left right"},
    {"left right", "left right"}
  };

  for(const auto& p : checks)
  {
    EXPECT_EQ(TrimAndCollapseWs(p.first), p.second);
  }
}

