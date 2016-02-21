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


namespace {


const char * nth_table_html =
"<html>"
  "<head></head>"
  "<body>"
    "<a    pos='1'  rev-pos='15' tag-pos='1' tag-rev-pos='8'></a>"
    "<h2   pos='2'  rev-pos='14' tag-pos='1' tag-rev-pos='1'></h2>"
    "<a    pos='3'  rev-pos='13' tag-pos='2' tag-rev-pos='7'></a>"
    "<span pos='4'  rev-pos='12' tag-pos='1' tag-rev-pos='2'></span>"
    "<div  pos='5'  rev-pos='11' tag-pos='1' tag-rev-pos='3'></div>"
    "<div  pos='6'  rev-pos='10' tag-pos='2' tag-rev-pos='2'></div>"
    "<a    pos='7'  rev-pos='9'  tag-pos='3' tag-rev-pos='6'></a>"
    "<a    pos='8'  rev-pos='8'  tag-pos='4' tag-rev-pos='5'></a>"
    "<span pos='9'  rev-pos='7'  tag-pos='2' tag-rev-pos='1'></span>"
    "<a    pos='10' rev-pos='6'  tag-pos='5' tag-rev-pos='4'></a>"
    "<a    pos='11' rev-pos='5'  tag-pos='6' tag-rev-pos='3'></a>"
    "<div  pos='12' rev-pos='4'  tag-pos='3' tag-rev-pos='1'></div>"
    "<a    pos='13' rev-pos='3'  tag-pos='7' tag-rev-pos='2'></a>"
    "<h1   pos='14' rev-pos='2'  tag-pos='1' tag-rev-pos='1'></h1>"
    "<a    pos='15' rev-pos='1'  tag-pos='8' tag-rev-pos='1'></a>"
  "</body>"
"</html>";


TEST(Pattern_NthChildMatch, Front)
{
  THtml h(nth_table_html);
  auto first_of_type = NthChildMatch::First | NthChildMatch::OfType;

  EXPECT_FALSE(NthChildMatch(2, 0).matches(h.body_child(1)));
  EXPECT_FALSE(NthChildMatch(2, 0).matches(h.body_child(15)));
  EXPECT_TRUE( NthChildMatch(2, 0).matches(h.body_child(2)));
  EXPECT_TRUE( NthChildMatch(2, 0).matches(h.body_child(14)));

  EXPECT_FALSE(NthChildMatch(2, 1).matches(h.body_child(2)));
  EXPECT_FALSE(NthChildMatch(2, 1).matches(h.body_child(14)));
  EXPECT_TRUE( NthChildMatch(2, 1).matches(h.body_child(1)));
  EXPECT_TRUE( NthChildMatch(2, 1).matches(h.body_child(15)));

  EXPECT_FALSE(NthChildMatch(-2, 15).matches(h.body_child(2)));
  EXPECT_FALSE(NthChildMatch(-2, 15).matches(h.body_child(14)));
  EXPECT_TRUE( NthChildMatch(-2, 15).matches(h.body_child(1)));
  EXPECT_TRUE( NthChildMatch(-2, 15).matches(h.body_child(15)));

  EXPECT_FALSE(NthChildMatch(2, 1, first_of_type).matches(h.body_child(15)));
  EXPECT_FALSE(NthChildMatch(2, 1, first_of_type).matches(h.body_child(9)));
  EXPECT_TRUE( NthChildMatch(2, 1, first_of_type).matches(h.body_child(4)));

  EXPECT_FALSE(NthChildMatch(0, 3).matches(h.body_child(6)));
  EXPECT_TRUE( NthChildMatch(0, 3).matches(h.body_child(3)));
}

TEST(Pattern_NthChildMatch, Back)
{
  THtml h(nth_table_html);
  auto last = NthChildMatch::Last;
  auto last_of_type = NthChildMatch::Last | NthChildMatch::OfType;

  EXPECT_FALSE(NthChildMatch(2, 0, last).matches(h.body_child(1)));
  EXPECT_FALSE(NthChildMatch(2, 0, last).matches(h.body_child(15)));
  EXPECT_TRUE( NthChildMatch(2, 0, last).matches(h.body_child(2)));
  EXPECT_TRUE( NthChildMatch(2, 0, last).matches(h.body_child(14)));

  EXPECT_FALSE(NthChildMatch(2, 1, last).matches(h.body_child(2)));
  EXPECT_FALSE(NthChildMatch(2, 1, last).matches(h.body_child(14)));
  EXPECT_TRUE( NthChildMatch(2, 1, last).matches(h.body_child(1)));
  EXPECT_TRUE( NthChildMatch(2, 1, last).matches(h.body_child(15)));

  EXPECT_FALSE(NthChildMatch(-2, 15, last).matches(h.body_child(2)));
  EXPECT_FALSE(NthChildMatch(-2, 15, last).matches(h.body_child(14)));
  EXPECT_TRUE( NthChildMatch(-2, 15, last).matches(h.body_child(1)));
  EXPECT_TRUE( NthChildMatch(-2, 15, last).matches(h.body_child(15)));

  EXPECT_FALSE(NthChildMatch(2, 1, last_of_type).matches(h.body_child(1)));
  EXPECT_FALSE(NthChildMatch(2, 1, last_of_type).matches(h.body_child(4)));
  EXPECT_TRUE( NthChildMatch(2, 1, last_of_type).matches(h.body_child(9)));

  EXPECT_FALSE(NthChildMatch(0, 3, last).matches(h.body_child(12)));
  EXPECT_TRUE( NthChildMatch(0, 3, last).matches(h.body_child(13)));
}

TEST(Pattern_NthChildMatch, ExampleFromDocumentation)
{
  {
    THtml h("<li>1</li><li>2</li><li>3</li>");
    NthChildMatch m_even(2, 0);
    NthChildMatch m_odd (2, 1);
    EXPECT_FALSE(m_even.matches(h.body_child(1)));
    EXPECT_TRUE( m_even.matches(h.body_child(2)));
    EXPECT_FALSE(m_even.matches(h.body_child(3)));
    EXPECT_TRUE(  m_odd.matches(h.body_child(1)));
    EXPECT_FALSE( m_odd.matches(h.body_child(2)));
    EXPECT_TRUE(  m_odd.matches(h.body_child(3)));
  }

  {
    THtml h(
      "<b>1</b>"
      "<u>2</u>"
      "<b>3</b>"
    );
    NthChildMatch m_last_of_type(
      0, 1, NthChildMatch::Last | NthChildMatch::OfType
    );
    EXPECT_FALSE(m_last_of_type.matches(h.body_child(1)));
    EXPECT_TRUE( m_last_of_type.matches(h.body_child(2)));
    EXPECT_TRUE( m_last_of_type.matches(h.body_child(3)));
  }
}


} // namespace

