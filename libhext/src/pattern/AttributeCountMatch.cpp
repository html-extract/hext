#include "hext/pattern/AttributeCountMatch.h"


namespace hext {


AttributeCountMatch::AttributeCountMatch(int attribute_count)
: attribute_count_(attribute_count > 0 ? attribute_count : 0)
{
}

MatchResult AttributeCountMatch::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return MatchResult(false, nullptr);

  unsigned int attr_count = GetNodeAttributeCount(node);
  return MatchResult(
    static_cast<unsigned int>(this->attribute_count_) == attr_count,
    nullptr
  );
}


} // namespace hext

