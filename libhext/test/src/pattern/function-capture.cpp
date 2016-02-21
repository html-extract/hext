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


TEST(Pattern_FunctionCapture, Captures)
{
  THtml h("<div>Inner Text</div>");
  FunctionCapture p(TextBuiltin, "result");
  auto pair = p.capture(h.first());
  EXPECT_TRUE(static_cast<bool>(pair));
  EXPECT_EQ(pair->first, "result");
  EXPECT_EQ(pair->second, "Inner Text");
}

TEST(Pattern_FunctionCapture, CapturesWithRegex)
{
  THtml h("<div>Inner Text</div>");
  FunctionCapture p(
    TextBuiltin,
    "result",
    std::make_unique<RegexPipe>(boost::regex("Inner (.*)"))
  );
  auto pair = p.capture(h.first());
  EXPECT_TRUE(static_cast<bool>(pair));
  EXPECT_EQ(pair->first, "result");
  EXPECT_EQ(pair->second, "Text");
}

TEST(Pattern_FunctionCapture, CustomFunction)
{
  const char * secret = "secret";
  CaptureFunction my_func = [secret](const GumboNode *) { return secret; };

  auto rpipe = std::make_unique<RegexPipe>(boost::regex("[a-z]{6}"));
  THtml h("<div>dummy</div>");
  for(auto cap : {FunctionCapture(my_func, "r", std::move(rpipe)),
                  FunctionCapture(my_func, "r")})
  {
    auto pair = cap.capture(h.first());
    EXPECT_TRUE(static_cast<bool>(pair));
    EXPECT_EQ(pair->first, "r");
    EXPECT_EQ(pair->second, "secret");
  }
}

TEST(Pattern_FunctionCapture, ExampleFromDocumentation)
{
  {
    THtml h("<div>5 reasons why foo is better than bar</div>");
    FunctionCapture text(TextBuiltin, "text");
    auto result = text.capture(h.first());
    ASSERT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(*result, ResultPair("text", "5 reasons why foo is better than bar"));
  }

  {
    THtml h("<div>The result is 25cm.</div>");
    FunctionCapture centimeters(
        InnerHtmlBuiltin,
        "centimeters",
        std::make_unique<RegexPipe>(boost::regex("(\\d+)cm")));
    auto result = centimeters.capture(h.first());
    ASSERT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(*result, ResultPair("centimeters", "25"));
  }
}

