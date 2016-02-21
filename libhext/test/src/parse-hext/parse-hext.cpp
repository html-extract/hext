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


TEST(ParseHext_ParseHext, ExampleFromDocumentation)
{
  EXPECT_NO_THROW(ParseHext("<a href:link />"));

  std::string hext_str("<a href:link />");
  EXPECT_NO_THROW(ParseHext(hext_str.c_str(), hext_str.size()));
}

TEST(ParseHext_ParseHext, ThrowsSyntaxError)
{
  EXPECT_THROW(ParseHext("invalid"), SyntaxError);
}

