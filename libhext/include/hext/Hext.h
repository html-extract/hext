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

