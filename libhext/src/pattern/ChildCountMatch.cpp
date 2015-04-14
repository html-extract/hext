#include "hext/pattern/ChildCountMatch.h"


namespace hext {


ChildCountMatch::ChildCountMatch(int child_count)
: child_count_(child_count > 0 ? child_count : 0)
{
}

bool ChildCountMatch::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  return
    static_cast<unsigned int>(this->child_count_) == GetNodeChildCount(node);
}


} // namespace hext

