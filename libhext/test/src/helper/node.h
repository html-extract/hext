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

#ifndef TEST_HELPER_NODE_H
#define TEST_HELPER_NODE_H

#include "gtest/gtest.h"

#include "hext/Hext.h"

#include <cassert>
#include <string>

#include <gumbo.h>


hext::HtmlTag tag(const GumboNode * node);
std::string attr_value(const GumboNode * node, const char * attr_name);


#endif // TEST_HELPER_NODE_H

