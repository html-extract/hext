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

RulePatterns::~RulePatterns()
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

  std::vector<const GumboAttribute *> m_attrs;
  for(const auto& p : this->matchp_)
  {
    // std::pair<bool has_matched, const GumboAttribute *> MatchResult
    MatchResult mr = p->matches(node);
    if( !mr.first )
      return false;
    else if( mr.second )
      m_attrs.push_back(mr.second);
  }

  // check if we have found _every_ attribute of GumboNode
  const GumboVector& v = node->v.element.attributes;
  for(unsigned int i = 0; i < v.length; ++i)
    if( std::find(m_attrs.begin(), m_attrs.end(), v.data[i]) == m_attrs.end() )
      return false;

  return true;
}

std::unique_ptr<MatchTree>
RulePatterns::capture(const GumboNode * node) const
{
  std::unique_ptr<MatchTree> mt = make_unique<MatchTree>();

  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return mt;

  for(const auto& p : this->capturep_)
    mt->append_match(p->capture(node));

  return mt;
}

void RulePatterns::print(std::ostream& out) const
{
  for(const auto& p : this->matchp_)
    p->print(out);
  for(const auto& p : this->capturep_)
    p->print(out);
}


} // namespace hext

