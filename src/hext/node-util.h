#ifndef HEXT_NODE_UTIL_H
#define HEXT_NODE_UTIL_H

#include <cassert>

#include <gumbo.h>


namespace hext {


/// Get the position of node within its parent. Only counts nodes of type
/// GUMBO_NODE_ELEMENT. First node has position 1. Returns 0 if no parent.
unsigned int get_node_position_within_parent(const GumboNode * node);


} // namespace hext


#endif // HEXT_NODE_UTIL_H

