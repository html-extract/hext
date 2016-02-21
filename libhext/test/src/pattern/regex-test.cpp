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


TEST(Pattern_RegexTest, Succeeds)
{
  {
    RegexTest has_number(boost::regex("\\d+"));
    EXPECT_TRUE(has_number.test("Nr. 23!"));
    EXPECT_TRUE(has_number.test("23"));
  }

  {
    RegexTest is_date(boost::regex("^\\d{2}-\\d{2}-\\d{4}$"));
    EXPECT_TRUE(is_date.test("01-01-1970"));
    EXPECT_TRUE(is_date.test("19-01-2038"));
  }
}

TEST(Pattern_RegexTest, Fails)
{
  {
    RegexTest has_number(boost::regex("\\d+"));
    EXPECT_FALSE(has_number.test("foo"));
  }

  {
    RegexTest is_date(boost::regex("^\\d{2}-\\d{2}-\\d{4}$"));
    EXPECT_FALSE(is_date.test("09-09-99"));
    EXPECT_FALSE(is_date.test("Born on 09-09-1941."));
  }
}

