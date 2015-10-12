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

#include "hext/NthChildMatch.h"

#include <cassert>


namespace hext {


NthChildMatch::NthChildMatch(int    step,
                             int    shift,
                             Option options) noexcept
: step_(step)
, shift_(shift)
, options_(options)
{
}

NthChildMatch::NthChildMatch(std::pair<int, int> step_and_shift,
                             Option              options) noexcept
: step_(step_and_shift.first)
, shift_(step_and_shift.second)
, options_(options)
{
}

bool NthChildMatch::matches(const GumboNode * node) const noexcept
{
  assert(node);
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  HtmlTag count_tag = HtmlTag::ANY;
  if( this->options_ & Option::OfType )
    count_tag = static_cast<HtmlTag>(node->v.element.tag);

  int node_pos = 0;
  if( this->options_ & Option::First )
    node_pos = this->count_preceding_siblings(node, count_tag);
  else
    node_pos = this->count_following_siblings(node, count_tag);

  // If step is zero, the user gave a specific number of the child element to
  // match. E.g. nth-child(23) or nth-child(0n+23).
  if( !this->step_ )
    return node_pos == this->shift_;

  if( this->step_ > 0 )
  {
    // If step is positive, but the node is positioned before the shift, it
    // cannot possibly match.
    if( node_pos < this->shift_ )
      return false;

    // If step is positive, and the node is positioned after or equal to the
    // shift it must be a multiple of step, or it doesn't match.
    return ( node_pos - this->shift_ ) % this->step_ == 0;
  }
  else
  {
    // Since step is negative, the node must be positioned before or equal to
    // the shift.
    if( node_pos > this->shift_ )
      return false;

    return ( this->shift_ - node_pos ) % ( -1 * this->step_ ) == 0;
  }
}

int NthChildMatch::count_preceding_siblings(
    const GumboNode * node,
    HtmlTag           count_tag) const noexcept
{
  assert(node);
  if( !node )
    return 0;

  const GumboNode * parent = node->parent;
  if( !parent || /* should never happen: */ parent->type != GUMBO_NODE_ELEMENT )
    return 0;

  int count = 0;
  const GumboVector& child_nodes = parent->v.element.children;
  assert(node->index_within_parent < child_nodes.length);
  // We only have to traverse up to node->index_within_parent, and not the
  // whole GumboVector. node->index_within_parent includes text nodes.
  for(unsigned int i = 0; i <= node->index_within_parent; ++i)
  {
    assert(i < child_nodes.length);
    auto child = static_cast<const GumboNode *>(child_nodes.data[i]);

    if( child && child->type == GUMBO_NODE_ELEMENT )
      if( count_tag == HtmlTag::ANY
          || child->v.element.tag == static_cast<GumboTag>(count_tag) )
        ++count;

    if( node == child )
      return count;
  }

  return 0;
}

int NthChildMatch::count_following_siblings(
    const GumboNode * node,
    HtmlTag           count_tag) const noexcept
{
  assert(node);
  if( !node )
    return 0;

  const GumboNode * parent = node->parent;
  if( !parent || /* should never happen: */ parent->type != GUMBO_NODE_ELEMENT )
    return 0;

  const GumboVector& child_nodes = parent->v.element.children;
  if( !child_nodes.length )
    return 0;

  assert(node->index_within_parent < child_nodes.length);
  int count = 0;
  // We only have to traverse down to node->index_within_parent, and not the
  // whole GumboVector. node->index_within_parent includes text nodes.
  for(unsigned int i = child_nodes.length; i-- > node->index_within_parent; )
  {
    assert(i < child_nodes.length);
    auto child = static_cast<const GumboNode *>(child_nodes.data[i]);

    assert(child != nullptr);
    if( child && child->type == GUMBO_NODE_ELEMENT )
      if( count_tag == HtmlTag::ANY ||
          child->v.element.tag == static_cast<GumboTag>(count_tag) )
        ++count;

    if( node == child )
      return count;
  }

  return 0;
}


} // namespace hext

