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


TEST(StringUtil_PrintNumberedLines, Empty)
{
  const char * dummy = "dummy";
  std::stringstream ss;
  PrintNumberedLines(dummy, dummy, ss);
  EXPECT_TRUE(ss.str().empty());
}

TEST(StringUtil_PrintNumberedLines, PrintsNumbers)
{
  const char * begin = "This\nis\na\nstring\nin\na\nsentence\n";
  const char * end = begin + std::strlen(begin);
  std::string expected =
    "1: This\n"
    "2: is\n"
    "3: a\n"
    "4: string\n"
    "5: in\n"
    "6: a\n"
    "7: sentence\n"
    "8: \n";

  std::stringstream ss;
  PrintNumberedLines(begin, end, ss);
  std::string result = ss.str();
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(expected, result);
}

