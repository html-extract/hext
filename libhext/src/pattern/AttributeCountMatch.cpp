#include "hext/pattern/AttributeCountMatch.h"


namespace hext {


AttributeCountMatch::AttributeCountMatch(int attribute_count)
: attribute_count_(attribute_count > 0 ? attribute_count : 0)
{
}

bool AttributeCountMatch::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  unsigned int attr_count = GetNodeAttributeCount(node);
  return static_cast<unsigned int>(this->attribute_count_) == attr_count;
}


} // namespace hext

