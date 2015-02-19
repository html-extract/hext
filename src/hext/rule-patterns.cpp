#include "hext/rule-patterns.h"


namespace hext {


rule_patterns::rule_patterns(
  std::vector<std::unique_ptr<match_pattern>>&& match_patterns,
  std::vector<std::unique_ptr<capture_pattern>>&& capture_patterns
)
: matchp(std::move(match_patterns))
, capturep(std::move(capture_patterns))
{
}

rule_patterns::~rule_patterns()
{
}

bool rule_patterns::matches(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  for(const auto& p : this->matchp)
    if( !p->matches(node).first )
      return false;

  return true;
}

bool rule_patterns::matches_all_attributes(const GumboNode * node) const
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  std::vector<const GumboAttribute *> m_attrs;
  for(const auto& p : this->matchp)
  {
    // std::pair<bool has_matched, const GumboAttribute *> match_result
    match_result mr = p->matches(node);
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

std::unique_ptr<match_tree>
rule_patterns::capture(const GumboNode * node) const
{
  std::unique_ptr<match_tree> mt = make_unique<match_tree>();

  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return mt;

  for(const auto& p : this->capturep)
    mt->append_match(p->capture(node));

  return mt;
}

void rule_patterns::print(std::ostream& out) const
{
  for(const auto& p : this->matchp)
    p->print(out);
  for(const auto& p : this->capturep)
    p->print(out);
}


} // namespace hext

