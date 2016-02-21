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

#include <cstring>

TEST(StringUtil_CharPosition, Position)
{
  const char * begin = "This\nis\na\nstring\nin\na\nsentence\n";
  const char * end = begin + std::strlen(begin);
  int char_count = 0;
  int line_count = 0;

  for(const char * c = begin; c != end; ++c)
  {
    EXPECT_EQ(CharPosition(begin, c), CharPosPair(line_count, char_count));
    if( *c == '\n' )
    {
      line_count++;
      char_count = 0;
    }
    else
    {
      char_count++;
    }
  }
}

