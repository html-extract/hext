#include "hext/pattern/NegateMatch.h"

#include <cassert>
#include <utility>


namespace hext {


NegateMatch::NegateMatch(
  std::vector<std::unique_ptr<MatchPattern>>&& match_patterns
)
: match_patterns_(std::move(match_patterns))
{
}

void NegateMatch::take_match(std::unique_ptr<MatchPattern>&& pattern)
{
  this->match_patterns_.push_back(std::move(pattern));
}

bool NegateMatch::matches(const GumboNode * node) const
{
  assert(node);
  if( !node )
    return true;

  for(const auto& mp : this->match_patterns_)
    if( mp && mp->matches(node) )
      return false;

  return true;
}


} // namespace hext

