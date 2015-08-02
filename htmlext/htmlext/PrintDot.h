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

