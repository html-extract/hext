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


TEST(Pipe_CollapseWsPipe, EmptyString)
{
  CollapseWsPipe p;
  EXPECT_EQ(p.transform(""), "");
  EXPECT_EQ(p.transform(" "), "");
  EXPECT_EQ(p.transform("  "), "");
  EXPECT_EQ(p.transform("   "), "");
}

TEST(Pipe_CollapseWsPipe, AlreadyTrimmed)
{
  CollapseWsPipe p;
  EXPECT_EQ(p.transform("a"), "a");
}

TEST(Pipe_CollapseWsPipe, Trim)
{
  CollapseWsPipe p;
  EXPECT_EQ(p.transform(" \n left"), "left");
  EXPECT_EQ(p.transform("right \n "), "right");
  EXPECT_EQ(p.transform("   \t leftright \n "), "leftright");
}

TEST(Pipe_CollapseWsPipe, Collapse)
{
  CollapseWsPipe p;
  std::vector<std::pair<std::string, std::string>> checks = {
    {"   \t l  e ftr    ig \n\t\r ht \n ", "l e ftr ig ht"},
    {"left           right", "left right"},
    {"left           right ", "left right"},
    {"left\nright", "left right"},
    {"left right", "left right"}
  };

  for(const auto& pair : checks)
  {
    EXPECT_EQ(p.transform(pair.first), pair.second);
  }
}

