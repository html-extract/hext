#ifndef HEXT_MATCHCONTEXT_H_INCLUDED
#define HEXT_MATCHCONTEXT_H_INCLUDED

#include <utility>
#include <vector>
#include <cstddef>

#include <gumbo.h>
#include <boost/optional.hpp>


namespace hext {

class Rule;

class MatchContext
{
public:
  typedef std::vector<std::pair<const Rule *, const GumboNode *>> match_group;
  typedef std::vector<Rule>::const_iterator rule_iter;

  MatchContext(
    rule_iter rule_begin,
    rule_iter rule_end,
    const GumboVector * nodes
  );

  boost::optional<match_group> match_next();

private:
  rule_iter next_mandatory_rule(rule_iter it) const;

  rule_iter r_begin_;
  rule_iter r_end_;
  std::size_t r_manda_cnt_;

  const GumboVector * nodes_;
  unsigned int current_node_;
};


} // namespace hext


#endif // HEXT_MATCHCONTEXT_H_INCLUDED

