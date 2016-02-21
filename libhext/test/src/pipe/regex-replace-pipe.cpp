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


TEST(Pipe_RegexReplacePipe, Replaces)
{
  {
    RegexReplacePipe r(boost::regex("Number \\d+"), "Number 23");
    EXPECT_EQ(r.transform("My Number? Number 42"), "My Number? Number 23");
  }
  {
    RegexReplacePipe r(boost::regex("Number"), "Potato");
    EXPECT_EQ(r.transform("My Number? Number 42"), "My Potato? Potato 42");
  }
  {
    RegexReplacePipe r(boost::regex(" Number"), "");
    EXPECT_EQ(r.transform("My Number? Number 42"), "My? 42");
  }
}

TEST(Pipe_RegexReplacePipe, ExampleFromDocumentation)
{
  RegexReplacePipe r(boost::regex("^(\\w+) (\\w+)$"), "$2 $1");
  EXPECT_EQ(r.transform("first second"), "second first");
}

