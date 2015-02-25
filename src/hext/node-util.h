#ifndef HEXT_NODE_UTIL_H
#define HEXT_NODE_UTIL_H

#include <cassert>
#include <string>

#include <gumbo.h>

#include "hext/string-util.h"


namespace hext {


/// Get the position of node within its parent. Only counts nodes of type
/// GUMBO_NODE_ELEMENT. First node has position 1. Returns 0 if no parent.
unsigned int GetNodePositionWithinParent(const GumboNode * node);

/// Get node's inner text. Uses hext::trim_and_collapse_ws.
std::string GetNodeText(const GumboNode * node);

/// Get node's inner text, as is.
std::string GetNodeRawText(const GumboNode * node);

/// Get node's inner html.
std::string GetNodeInnerHtml(const GumboNode * node);


} // namespace hext


#endif // HEXT_NODE_UTIL_H

