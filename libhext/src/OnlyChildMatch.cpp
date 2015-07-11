#include "hext/OnlyChildMatch.h"

#include <cassert>


namespace hext {


bool OnlyChildMatch::matches(const GumboNode * node) const
{
  assert(node);
  if( !node )
    return false;

  const GumboNode * parent = node->parent;
  if( !parent || parent->type != GUMBO_NODE_ELEMENT )
    return false;

  const GumboVector& child_nodes = parent->v.element.children;
  for(unsigned int i = 0; i < child_nodes.length; ++i)
  {
    auto child = static_cast<const GumboNode *>(child_nodes.data[i]);

    if( child && child->type == GUMBO_NODE_ELEMENT && node != child )
      return false;
  }

  return true;
}


} // namespace hext

