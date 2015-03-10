#include "hext/rule-patterns.h"


namespace hext {


RulePatterns::RulePatterns(
  std::vector<std::unique_ptr<MatchPattern>>&& match_patterns,
  std::vector<std::unique_ptr<CapturePattern>>&& capture_patterns
)
: matchp_(std::move(match_patterns))
, capturep_(std::move(capture_patterns))
{
}

bool RulePatterns::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  for(const auto& p : this->matchp_)
    if( !p->matches(node).first )
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
  for(const auto& pattern : this->matchp_)
  {
    MatchResult mr = pattern->matches(node);
    if( !mr.first /* hasn't matched? */ )
      return false;
    else if( mr.second /* matched GumboAttribute pointer is not null? */ )
      m_attrs.push_back(mr.second);
  }

  const GumboVector& v = node->v.element.attributes;
  // Check if we have matched _every_ attribute of GumboNode. This is O(N^2).
  for(unsigned int i = 0; i < v.length; ++i)
    if( std::find(m_attrs.begin(), m_attrs.end(), v.data[i]) == m_attrs.end() )
      return false;

  return true;
}

std::unique_ptr<ResultTree>
RulePatterns::capture(const GumboNode * node) const
{
  std::unique_ptr<ResultTree> rt = MakeUnique<ResultTree>();

  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return rt;

  for(const auto& p : this->capturep_)
    rt->append_result(p->capture(node));

  return rt;
}

void RulePatterns::print(std::ostream& out) const
{
  for(const auto& p : this->matchp_)
    p->print(out);
  for(const auto& p : this->capturep_)
    p->print(out);
}


} // namespace hext

