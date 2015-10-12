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

#include "gtest/gtest.h"

#include "StringUtil.h"
#include "hext/Hext.h"

#include "helper/html.h"
#include "helper/node.h"

using namespace hext;
using namespace helper;
#include "pattern/attribute-capture.h"
#include "pattern/attribute-count-match.h"
#include "pattern/attribute-match.h"
#include "pattern/begins-with-test.h"
#include "pattern/child-count-match.h"
#include "pattern/contains-test.h"
#include "pattern/contains-words-test.h"
#include "pattern/ends-with-test.h"
#include "pattern/equals-test.h"
#include "pattern/function-capture.h"
#include "pattern/function-match.h"
#include "pattern/function-value-match.h"
#include "pattern/negate-match.h"
#include "pattern/negate-test.h"
#include "pattern/nth-child-match.h"
#include "pattern/only-child-match.h"
#include "pattern/regex-test.h"

#include "builtins/inner-html-builtin.h"
#include "builtins/strip-tags-builtin.h"
#include "builtins/text-builtin.h"

#include "string-util/char-position.h"
#include "string-util/is-space.h"
#include "string-util/print-numbered-lines.h"
#include "string-util/trim-and-collapse-ws.h"

#include "html-tag/html-tag.h"
#include "html/html.h"
#include "parse-hext/parse-hext.h"
#include "rule/rule.h"
#include "rule/rule-matching.h"

#include "pipe/append-pipe.h"
#include "pipe/case-pipe.h"
#include "pipe/prepend-pipe.h"
#include "pipe/regex-pipe.h"
#include "pipe/regex-replace-pipe.h"
#include "pipe/string-pipe.h"
#include "pipe/trim-pipe.h"


int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

