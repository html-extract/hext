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

#include "hext/AttributeCountMatch.h"

#include <cassert>


namespace hext {


AttributeCountMatch::AttributeCountMatch(unsigned int attribute_count) noexcept
: attribute_count_(attribute_count)
{
}

bool AttributeCountMatch::matches(const GumboNode * node) const noexcept
{
  assert(node);
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  unsigned int attr_count = node->v.element.attributes.length;
  return this->attribute_count_ == attr_count;
}


} // namespace hext

