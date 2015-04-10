#include "hext/RulePatterns.h"


namespace hext {


RulePatterns::RulePatterns(
  std::vector<std::unique_ptr<MatchPattern>>&& match_patterns,
  std::vector<std::unique_ptr<CapturePattern>>&& capture_patterns
)
: match_patterns_(std::move(match_patterns))
, capture_patterns_(std::move(capture_patterns))
{
}

bool RulePatterns::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  for(const auto& pattern : this->match_patterns_)
    if( !pattern->matches(node).first )
      return false;

  return true;
}

std::vector<ResultPair> RulePatterns::capture(const GumboNode * node) const
{
  typedef std::vector<ResultPair> values_type;
  typedef std::vector<std::unique_ptr<CapturePattern>> patterns_type;

  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return values_type();

  patterns_type::size_type patterns_size = this->capture_patterns_.size();
  values_type values(patterns_size);
  for(patterns_type::size_type i = 0; i < patterns_size; ++i)
    values[i] = this->capture_patterns_[i]->capture(node);

  return values;
}


} // namespace hext

