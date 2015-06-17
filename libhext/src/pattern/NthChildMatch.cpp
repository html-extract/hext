#include "hext/pattern/NthChildMatch.h"


namespace hext {


NthChildMatch::NthChildMatch(
  int step,
  int shift,
  GumboTag count_tag,
  OffsetOf offset_of
)
: step_(step)
, shift_(shift)
, count_tag_(count_tag)
, offset_of_(offset_of)
{
}

bool NthChildMatch::matches(const GumboNode * node) const
{
  assert(node);
  if( !node )
    return false;

  int node_pos = 0;
  if( this->offset_of_ == OffsetOf::Front )
    node_pos = GetNodePositionWithinParent(node, this->count_tag_);
  else
    node_pos = GetNodePositionWithinParentReverse(node, this->count_tag_);

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


} // namespace hext

