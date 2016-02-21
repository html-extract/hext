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


TEST(Pattern_AttributeCapture, Captures)
{
  THtml h("<div class='class-value'></div>");
  AttributeCapture p("class", "result");
  auto pair = p.capture(h.first());
  EXPECT_TRUE(static_cast<bool>(pair));
  EXPECT_EQ(pair->first, "result");
  EXPECT_EQ(pair->second, "class-value");
}

TEST(Pattern_AttributeCapture, CapturesWithRegex)
{
  THtml h("<div class='class-value'></div>");
  AttributeCapture p(
      "class",
      "result",
      std::make_unique<RegexPipe>(boost::regex("class-(.*)")));
  auto pair = p.capture(h.first());
  EXPECT_TRUE(static_cast<bool>(pair));
  EXPECT_EQ(pair->first, "result");
  EXPECT_EQ(pair->second, "value");
}

TEST(Pattern_AttributeCapture, MissingAttrReturnsEmpty)
{
  THtml h("<div nope='nope'></div>");
  AttributeCapture p("class", "result");
  auto pair = p.capture(h.first());
  EXPECT_FALSE(static_cast<bool>(pair));
}

TEST(Pattern_AttributeCapture, ExampleFromDocumentation)
{
  {
    THtml h("<img src='bob.jpg'/>");
    AttributeCapture img("src", "image");
    auto result = img.capture(h.first());
    ASSERT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(*result, ResultPair("image", "bob.jpg"));
  }

  {
    THtml h("<a href='/highway-61'></a>");
    AttributeCapture highway(
        "href",
        "U.S. Route",
        std::make_unique<RegexPipe>(boost::regex("\\d+")));
    auto result = highway.capture(h.first());
    ASSERT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(*result, ResultPair("U.S. Route", "61"));
  }
}

