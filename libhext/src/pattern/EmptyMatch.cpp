#include "hext/pattern/EmptyMatch.h"


namespace hext {


MatchResult EmptyMatch::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return MatchResult(false, nullptr);

  return MatchResult(!node->v.element.children.length, nullptr);
}


} // namespace hext

