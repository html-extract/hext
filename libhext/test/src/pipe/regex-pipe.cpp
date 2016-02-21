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


TEST(Pipe_RegexPipe, Filters)
{
  RegexPipe def(boost::regex("Number (\\d+)"));
  EXPECT_EQ(def.transform("Number 42"), "42");
}

TEST(Pipe_RegexPipe, ExamplesFromDocumentation)
{
  std::string input = "Highway 61 revisited";

  const std::pair<const char *, const char *> checks[] = {
    {"\\d+", "61"},
    {"Highway \\d+", "Highway 61"},
    {"Highway (\\d+)", "61"},
    {"\\w+", "Highway"},
    {"(\\w+) (\\d+)", "Highway"}
  };

  for(auto p : checks)
  {
    RegexPipe def(boost::regex(p.first));
    EXPECT_EQ(def.transform(input), p.second);
  }
}

