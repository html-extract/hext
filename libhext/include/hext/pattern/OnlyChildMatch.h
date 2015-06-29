#ifndef HEXT_PATTERN_ONLY_CHILD_MATCH_H_INCLUDED
#define HEXT_PATTERN_ONLY_CHILD_MATCH_H_INCLUDED

#include "hext/pattern/MatchPattern.h"

#include <cassert>

#include <gumbo.h>


namespace hext {


/// Matches if a node is the only child of its parent.
class OnlyChildMatch : public MatchPattern
{
public:
  /// Return true if node is the only child of its parent.
  bool matches(const GumboNode * node) const final
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
};


} // namespace hext


#endif // HEXT_PATTERN_ONLY_CHILD_MATCH_H_INCLUDED

