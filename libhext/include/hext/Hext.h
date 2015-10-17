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

#ifndef HEXT_HEXT_H_INCLUDED
#define HEXT_HEXT_H_INCLUDED

/// @file
///   Convenience header that includes all of hext.


// Extraction
#include "hext/Html.h"
#include "hext/HtmlTag.h"
#include "hext/Result.h"
#include "hext/Rule.h"


// Parsing
#include "hext/ParseHext.h"
#include "hext/SyntaxError.h"


// Captures
#include "hext/Capture.h"
#include "hext/AttributeCapture.h"
#include "hext/FunctionCapture.h"
#include "hext/CaptureFunction.h"
#include "hext/Builtins.h"


// Pipes
#include "hext/StringPipe.h"
#include "hext/AppendPipe.h"
#include "hext/CasePipe.h"
#include "hext/CollapseWsPipe.h"
#include "hext/PrependPipe.h"
#include "hext/RegexPipe.h"
#include "hext/RegexReplacePipe.h"
#include "hext/TrimPipe.h"


// Matches
#include "hext/Match.h"
#include "hext/AttributeCountMatch.h"
#include "hext/AttributeMatch.h"
#include "hext/ChildCountMatch.h"
#include "hext/FunctionMatch.h"
#include "hext/FunctionValueMatch.h"
#include "hext/MatchFunction.h"
#include "hext/NegateMatch.h"
#include "hext/NthChildMatch.h"
#include "hext/OnlyChildMatch.h"


// ValueTests
#include "hext/ValueTest.h"
#include "hext/BeginsWithTest.h"
#include "hext/ContainsTest.h"
#include "hext/ContainsWordsTest.h"
#include "hext/EndsWithTest.h"
#include "hext/EqualsTest.h"
#include "hext/NegateTest.h"
#include "hext/RegexTest.h"


// Helpers
#include "hext/Cloneable.h"


// Version
#include "hext/Version.h"


#endif // HEXT_HEXT_H_INCLUDED

