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
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  int node_pos = 0;
  if( this->offset_of_ == OffsetOf::Front )
    node_pos = GetNodePositionWithinParent(node, this->count_tag_);
  else
    node_pos = GetNodePositionWithinParentReverse(node, this->count_tag_);

  if( this->step_ )
    return node_pos % this->step_ == this->shift_ % this->step_;
  else
    return node_pos == this->shift_;
}


} // namespace hext

