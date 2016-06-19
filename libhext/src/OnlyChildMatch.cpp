// Copyright 2015, 2016 Thomas Trapp
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

#include "hext/OnlyChildMatch.h"

#include <cassert>


namespace hext {


OnlyChildMatch::OnlyChildMatch(Option options) noexcept
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

