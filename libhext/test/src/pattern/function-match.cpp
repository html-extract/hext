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


TEST(Pattern_FunctionMatch, Matches)
{
  THtml h("<div></div>");

  MatchFunction is_div = [](const GumboNode * node) {
    return node->type == GUMBO_NODE_ELEMENT &&
           node->v.element.tag == GUMBO_TAG_DIV;
  };

  EXPECT_TRUE(FunctionMatch(is_div).matches(h.first()));
}

TEST(Pattern_FunctionMatch, Fails)
{
  THtml h("<span></span>");

  MatchFunction is_div = [](const GumboNode * node) {
    return node->type == GUMBO_NODE_ELEMENT &&
           node->v.element.tag == GUMBO_TAG_DIV;
  };

  EXPECT_FALSE(FunctionMatch(is_div).matches(h.first()));
}

