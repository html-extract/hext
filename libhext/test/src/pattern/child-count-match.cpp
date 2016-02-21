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


TEST(Pattern_ChildCountMatch, Matches)
{
  {
    THtml h("<div></div>");
    EXPECT_TRUE(ChildCountMatch(0).matches(h.first()));
  }

  {
    THtml h(
      "<div>\
        <hr>\
        <hr>\
        <hr>\
        <hr>\
        <hr>\
      </div>");
    EXPECT_TRUE(ChildCountMatch(5).matches(h.first()));
  }
}

TEST(Pattern_ChildCountMatch, Fails)
{
  THtml h(
    "<div>\
      <hr>\
      <hr>\
      <hr>\
      <hr>\
      <hr>\
    </div>");

  for(unsigned int i : {1u,2u,3u,4u,6u,7u,8u,9u,10u})
    EXPECT_FALSE(ChildCountMatch(i).matches(h.first()));
}

