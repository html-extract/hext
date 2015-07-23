#include "hext/OnlyChildMatch.h"

#include <cassert>


namespace hext {


OnlyChildMatch::OnlyChildMatch(Option options)
: options_(options)
{
}

bool OnlyChildMatch::matches(const GumboNode * node) const noexcept
{
  assert(node);
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  const GumboNode * parent = node->parent;
  if( !parent || parent->type != GUMBO_NODE_ELEMENT )
    return false;

  GumboTag count_tag = node->v.element.tag;

  const GumboVector& child_nodes = parent->v.element.children;
  for(unsigned int i = 0; i < child_nodes.length; ++i)
  {
    auto child = static_cast<const GumboNode *>(child_nodes.data[i]);

    if( child && child->type == GUMBO_NODE_ELEMENT && node != child )
      if( !(this->options_ & OfType) || child->v.element.tag == count_tag )
        return false;
  }

  return true;
}


} // namespace hext

