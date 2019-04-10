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
#include <utility>

TEST(Rule_Rule, ExampleFromDocumentation)
{
  Rule anchor(HtmlTag::A);
  anchor.append_match<AttributeMatch>("href")
        .append_capture<AttributeCapture>("href", "link");
  {
    Rule img(HtmlTag::IMG);
    img.append_capture<AttributeCapture>("src", "img");
    anchor.append_child(std::move(img));
  }

  // <a href:link><img src:img/></a>
  Html html(
    "<html><body>"
      "<div><a href='/bob'>  <img src='bob.jpg'/>  </a></div>"
      "<div><a href='/alice'><img src='alice.jpg'/></a></div>"
      "<div><a href='/carol'><img src='carol.jpg'/></a></div>"
    "</body></html>");

  Result result = anchor.extract(html);

  Result expected = {
    {
      {"link", "/bob"},
      {"img", "bob.jpg"}
    },
    {
      {"link", "/alice"},
      {"img", "alice.jpg"}
    },
    {
      {"link", "/carol"},
      {"img", "carol.jpg"}
    }
  };

  EXPECT_EQ(result, expected);
}

TEST(Rule_Rule, SettersGetters)
{
  Rule r;

  // defaults
  EXPECT_EQ(r.get_tag(), HtmlTag::ANY);
  EXPECT_EQ(r.is_optional(), false);
  EXPECT_EQ(r.is_greedy(), false);

  auto copy = r;

  r.set_tag(HtmlTag::SPAN);
  r.set_optional(true);
  r.set_greedy(true);
  EXPECT_EQ(r.get_tag(), HtmlTag::SPAN);
  EXPECT_EQ(r.is_optional(), true);
  EXPECT_EQ(r.is_greedy(), true);

  EXPECT_EQ(copy.get_tag(), HtmlTag::ANY);
  EXPECT_EQ(copy.is_optional(), false);
  EXPECT_EQ(copy.is_greedy(), false);
}

TEST(Rule_Rule, Copy)
{
  THtml h("<a href='/page' class='link'>"
            "<img src='/img.png'/>"
            "<span>Page</span>"
          "</a>");

  // A rule tree that will produce capture groups with four results
  auto right = ParseHext("<a href^='/' class:type href:link >"   // 2 results
                           "<img src:img />"                     // 1 result
                           "<span @text:link_name />"            // 1 result
                         "</a>");

  ASSERT_TRUE(right.matches(h.first()));

  auto left = right;
  right = Rule();

  EXPECT_TRUE(left.matches(h.first()));
  EXPECT_FALSE(left.next());
  ASSERT_TRUE(left.child());
  ASSERT_TRUE(left.child()->next());
  EXPECT_FALSE(left.child()->next()->next());

  auto result = left.extract(h.root());
  ASSERT_EQ(result.size(), 1);
  EXPECT_EQ(result.front().size(), 4);
}

