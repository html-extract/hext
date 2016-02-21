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

#include <memory>

TEST(Pattern_AttributeMatch, Matches)
{
  auto test = std::make_unique<EqualsTest>("value");

  THtml h("<div class='value'></div>");
  EXPECT_TRUE(AttributeMatch("class").matches(h.first()));
  EXPECT_TRUE(AttributeMatch("class", std::move(test)).matches(h.first()));
}

TEST(Pattern_AttributeMatch, Fails)
{
  auto test = std::make_unique<EqualsTest>("value");

  THtml h("<div class='nope'></div>");
  EXPECT_FALSE(AttributeMatch("clas").matches(h.first()));
  EXPECT_FALSE(AttributeMatch("nope").matches(h.first()));
  EXPECT_FALSE(AttributeMatch("class", std::move(test)).matches(h.first()));
}

