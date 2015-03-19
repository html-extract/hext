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

bool RulePatterns::matches_all_attributes(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  // In typical html, most html-nodes have few to no attributes at all.
  // Further, most nodes will not match.

  // Use a vector to store all pointers to previously matched GumboAttributes.
  // It is assumed that lookup in a contiguous data structure is faster than
  // e.g. std::map if the number of elements is very small.
  std::vector<const GumboAttribute *> m_attrs;
  for(const auto& pattern : this->match_patterns_)
  {
    // MatchResult is a pair. First member is a boolean, signaling whether the
    // match was successful. Second member is a pointer to the matched
    // GumboAttribute, if applicable. For example, BuiltinMatches are not
    // matched against GumboAttributes, therefore the pointer returned will
    // always be null.
    MatchResult mr = pattern->matches(node);
    if( !mr.first )
      return false;
    else if( mr.second )
      m_attrs.push_back(mr.second);
  }

  const GumboVector& v = node->v.element.attributes;
  // Check if we have matched _every_ attribute of GumboNode. This is O(N^2).
  for(unsigned int i = 0; i < v.length; ++i)
    if( std::find(m_attrs.begin(), m_attrs.end(), v.data[i]) == m_attrs.end() )
      return false;

  return true;
}

std::vector<ResultTree::NameValuePair>
RulePatterns::capture(const GumboNode * node) const
{
  typedef std::vector<ResultTree::NameValuePair> values_type;
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

