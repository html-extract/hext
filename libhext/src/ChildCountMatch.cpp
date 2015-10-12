// Copyright 2015 Thomas Trapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "hext/ChildCountMatch.h"

#include <cassert>


namespace hext {


ChildCountMatch::ChildCountMatch(unsigned int child_count) noexcept
: child_count_(child_count)
{
}

bool ChildCountMatch::matches(const GumboNode * node) const noexcept
{
  assert(node);
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  return this->child_count_ == this->count_child_elements(node);
}

unsigned int ChildCountMatch::count_child_elements(
    const GumboNode * node) const noexcept
{
  assert(node);
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return 0;

  unsigned int count = 0;
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

