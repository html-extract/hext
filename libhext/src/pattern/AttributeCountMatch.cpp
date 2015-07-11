#include "hext/pattern/AttributeCountMatch.h"

#include <cassert>


namespace hext {


AttributeCountMatch::AttributeCountMatch(int attribute_count)
: attribute_count_(attribute_count > 0 ? attribute_count : 0)
{
}

bool AttributeCountMatch::matches(const GumboNode * node) const
{
  assert(node);
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  int attr_count = node->v.element.attributes.length;
  return this->attribute_count_ == attr_count;
}


} // namespace hext

