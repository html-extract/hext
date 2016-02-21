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


TEST(Pipe_CasePipe, ChangesCase)
{
  {
    CasePipe p;
    EXPECT_EQ(p.transform("Word"), "word");
  }
  {
    CasePipe p(CasePipe::ToLower);
    EXPECT_EQ(p.transform("WoRd"), "word");
  }
  {
    CasePipe p(CasePipe::ToUpper);
    EXPECT_EQ(p.transform("Word"), "WORD");
  }
}

