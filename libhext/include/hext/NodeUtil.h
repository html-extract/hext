#ifndef HEXT_NODE_UTIL_H_INCLUDED
#define HEXT_NODE_UTIL_H_INCLUDED

#include "hext/StringUtil.h"

#include <cassert>
#include <string>
#include <cstddef>
#include <iterator>

#include <gumbo.h>


namespace hext {


/// Get the position of `node` within its parent. Only count nodes of type
/// `GUMBO_NODE_ELEMENT`. First node has position 1. Return 0 if no parent.
/// If `count_tag` is set to `GUMBO_TAG_UNKNOWN` all nodes are counted,
/// regardless of their tag name. If any other `GumboTag` is passed, count
/// only nodes that have a tag equal to `count_tag`.
unsigned int GetNodePositionWithinParent(
  const GumboNode * node,
  GumboTag count_tag = GUMBO_TAG_UNKNOWN
);

/// Get the position of `node` within its parent in reverse. Only count nodes
/// of type `GUMBO_NODE_ELEMENT`. Last node has position 1. Return 0 if no
/// parent. If `count_tag` is set to `GUMBO_TAG_UNKNOWN` all nodes are counted,
/// regardless of their tag name. If any other `GumboTag` is passed, count only
/// nodes that have tag equal to `count_tag`.
unsigned int GetNodePositionWithinParentReverse(
  const GumboNode * node,
  GumboTag count_tag = GUMBO_TAG_UNKNOWN
);

/// Return amount of node's attributes.
unsigned int GetNodeAttributeCount(const GumboNode * node);

/// Count amount of children with node type `GUMBO_NODE_ELEMENT` (which excludes
/// text-nodes).
unsigned int GetNodeChildCount(const GumboNode * node);

/// Get inner text of a `node`. Trim left and right whitespace and collapse
/// multiple whitespace into a single space.
std::string GetNodeText(const GumboNode * node);

/// Get inner text of a `node`, as is, untouched.
std::string GetNodeRawText(const GumboNode * node);

/// Get inner html of a `node`, as is, untouched.
std::string GetNodeInnerHtml(const GumboNode * node);

/// Return true if `tag` is a tag for an element that is to be embedded
/// in spaces when converting html to text (that excludes most inline
/// elements, e.g. `<span>`).
bool RequiresSpaces(GumboTag tag);


} // namespace hext


#endif // HEXT_NODE_UTIL_H_INCLUDED

