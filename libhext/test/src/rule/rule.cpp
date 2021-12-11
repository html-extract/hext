// Copyright 2015-2021 Thomas Trapp
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
  EXPECT_EQ(r.get_tagname(), std::nullopt);
  EXPECT_EQ(r.is_optional(), false);
  EXPECT_EQ(r.is_greedy(), false);

  auto copy = r;

  r.set_tag(HtmlTag::SPAN);
  r.set_tagname("span");
  r.set_optional(true);
  r.set_greedy(true);
  EXPECT_EQ(r.get_tag(), HtmlTag::SPAN);
  EXPECT_EQ(r.get_tagname(), std::string("span"));
  EXPECT_EQ(r.is_optional(), true);
  EXPECT_EQ(r.is_greedy(), true);

  EXPECT_EQ(copy.get_tag(), HtmlTag::ANY);
  EXPECT_EQ(copy.get_tagname(), std::nullopt);
  EXPECT_EQ(copy.is_optional(), false);
  EXPECT_EQ(copy.is_greedy(), false);
}

TEST(Rule_Rule, Copy)
{
  THtml h("<a href='/page' class='link'>"
            "<img src='/img.png'/>"
            "<custom-tag>Page</custom-tag>"
          "</a>");

  // A rule tree that will produce capture groups with four results
  auto right = ParseHext("<a href^='/' class:type href:link >"   // 2 results
                           "<img src:img />"                     // 1 result
                           "<custom-tag @text:link_name />"      // 1 result
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

TEST(Rule_Rule, TagNameIsConvertedToTag)
{
  Rule not_really_custom("img");
  EXPECT_EQ(not_really_custom.get_tag(), HtmlTag::IMG);
  EXPECT_FALSE(not_really_custom.get_tagname());

  Rule not_really_custom_ci("dIv");
  EXPECT_EQ(not_really_custom_ci.get_tag(), HtmlTag::DIV);
  EXPECT_FALSE(not_really_custom_ci.get_tagname());
}

TEST(Rule_Rule, MatchesCustomTags)
{
  Rule custom("yt-formatted-string");
  custom.append_match<AttributeMatch>("href")
        .append_capture<AttributeCapture>("href", "link");
  {
    Rule image("images");
    image.append_capture<AttributeCapture>("src", "img");
    custom.append_child(std::move(image));
  }

  // <yt-formatted-string href:link><images src:img/></yt-formatted-string>
  Html html(
    "<html><body>"
      "<div>"
        "<yt-formatted-string href='/bob'>"
          "<images src='bob.jpg' />"
        "</yt-formatted-string>"
      "</div>"
      "<div>"
        "<yt-formatted-string href='/alice'>"
          "<images src='alice.jpg' />"
        "</yt-formatted-string>"
      "</div>"
      "<div>"
        "<yt-formatted-string href='/carol'>"
          "<images src='carol.jpg' />"
        "</yt-formatted-string>"
      "</div>"
    "</body></html>");

  Result result = custom.extract(html);

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

TEST(Rule_Rule, EmptyTagNameDoesNotMatch)
{
  Rule empty("");
  empty.append_capture<AttributeCapture>("class", "y");

  Html html(
    "<html><body class='y'>"
      "<div class='y'></div>"
    "</body></html>");

  Result result = empty.extract(html);
  EXPECT_EQ(result.size(), 0);
}

TEST(Rule_Rule, NestedRule)
{
  Rule r(HtmlTag::BODY);
  {
    Rule inner(HtmlTag::SPAN);
    inner.append_capture<AttributeCapture>("class", "c");
    r.append_nested(inner);
  }

  Rule r2(r);
  r.nested().clear();

  Html html(
    "<html><body>"
      "<div><div><div><div><div><div>"
        "<span class='one'></span>"
        "<span class='two'></span>"
        "<span class='three'></span>"
      "</div></div></div></div></div></div>"
    "</body></html>"
  );

  Result empty_result = r.extract(html);
  EXPECT_EQ(empty_result.size(), 0);

  Result result = r2.extract(html);
  EXPECT_EQ(result.size(), 1);

  Result expected = {
    {
      {"c", "one"},
      {"c", "two"},
      {"c", "three"}
    }
  };

  EXPECT_EQ(result, expected);
}

