#ifndef HEXT_NODE_UTIL_H_INCLUDED
#define HEXT_NODE_UTIL_H_INCLUDED

#include "hext/StringUtil.h"

#include <cassert>
#include <string>
#include <cstddef>
#include <iterator>

#include <gumbo.h>


namespace hext {


/// Get the position of node within its parent. Only counts nodes of type
/// GUMBO_NODE_ELEMENT. First node has position 1. Returns 0 if no parent.
/// If count_tag is set to GUMBO_TAG_UNKNOWN all nodes are counted, regardless
/// of their tag name. If any other gumbo tag is passed, count only nodes that
/// have tag equal to count_tag.
unsigned int GetNodePositionWithinParent(
  const GumboNode * node,
  GumboTag count_tag = GUMBO_TAG_UNKNOWN
);

/// Get the position of node within its parent in reverse. Only counts nodes of
/// type GUMBO_NODE_ELEMENT. Last node has position 1. Returns 0 if no parent.
/// If count_tag is set to GUMBO_TAG_UNKNOWN all nodes are counted, regardless
/// of their tag name. If any other gumbo tag is passed, count only nodes that
/// have tag equal to count_tag.
unsigned int GetNodePositionWithinParentReverse(
  const GumboNode * node,
  GumboTag count_tag = GUMBO_TAG_UNKNOWN
);

/// Count amount of children. Only count children of type GUMBO_NODE_ELEMENT.
unsigned int GetNodeChildCount(const GumboNode * node);

/// Get node's inner text. Uses hext::trim_and_collapse_ws.
std::string GetNodeText(const GumboNode * node);

/// Get node's inner text, as is.
std::string GetNodeRawText(const GumboNode * node);

/// Get node's inner html as an untouched copy of the source buffer.
std::string GetNodeInnerHtml(const GumboNode * node);


} // namespace hext


#endif // HEXT_NODE_UTIL_H_INCLUDED

