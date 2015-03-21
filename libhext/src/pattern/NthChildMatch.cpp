#include "hext/pattern/NthChildMatch.h"


namespace hext {


NthChildMatch::NthChildMatch(int step, int shift, OffsetOf offset_of)
: step_(step)
, shift_(shift)
, offset_of_(offset_of)
{
}

MatchResult NthChildMatch::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return MatchResult(false, nullptr);

  int node_pos = 0;
  if( this->offset_of_ == OffsetOf::Front )
    node_pos = GetNodePositionWithinParent(node);
  else
    node_pos = GetNodePositionWithinParentReverse(node);

  if( this->step_ )
    return MatchResult(
      node_pos % this->step_ == this->shift_ % this->step_,
      nullptr
    );
  else
    return MatchResult(node_pos == this->shift_, nullptr);
}


} // namespace hext

