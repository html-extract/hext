#include "hext/ChildCountMatch.h"

#include <cassert>


namespace hext {


ChildCountMatch::ChildCountMatch(int child_count) noexcept
: child_count_(child_count > 0 ? child_count : 0)
{
}

bool ChildCountMatch::matches(const GumboNode * node) const noexcept
{
  assert(node);
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  return this->child_count_ == this->count_child_elements(node);
}

int ChildCountMatch::count_child_elements(const GumboNode * node) const noexcept
{
  assert(node);
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return 0;

  int count = 0;
  const GumboVector& children = node->v.element.children;
  for(unsigned int i = 0; i < children.length; ++i)
  {
    auto child = static_cast<const GumboNode *>(children.data[i]);
    if( child->type == GUMBO_NODE_ELEMENT )
      ++count;
  }

  return count;
}


} // namespace hext

