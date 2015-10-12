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

#ifndef HTMLEXT_PRINT_DOT_H_INCLUDED
#define HTMLEXT_PRINT_DOT_H_INCLUDED

#include "hext/Html.h"

#include <cassert>
#include <ostream>
#include <string>

#include <gumbo.h>


namespace htmlext {


/// Print HTML as DOT.
/// Example: htmlext --print-html-dot example.html
///          | dot -Tpng /dev/stdin -o example.graph.png
/// See https://en.wikipedia.org/wiki/DOT_%28graph_description_language%29
void PrintHtmlDot(const hext::Html& html, std::ostream& out);
void PrintHtmlDotNodes(const GumboNode * node, int parent_id, std::ostream& out);


} // namespace htmlext


#endif // HTMLEXT_PRINT_DOT_H_INCLUDED

