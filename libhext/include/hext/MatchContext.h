#ifndef HEXT_MATCHCONTEXT_H_INCLUDED
#define HEXT_MATCHCONTEXT_H_INCLUDED

#include <utility>
#include <vector>
#include <cstddef>

#include <boost/optional.hpp>
#include <gumbo.h>


namespace hext {


class Rule;


/// A MatchContext matches a group of rules against a GumboVector of nodes.
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

  /// Return next match_group. Returns empty if there are no more matches.
  boost::optional<match_group> match_next();

private:
  /// Return the next mandatory rule after `it`.
  /// Return this->r_end_ if there are no mandatory rules.
  rule_iter next_mandatory_rule(rule_iter it) const;

  rule_iter r_begin_;
  rule_iter r_end_;

  const GumboVector * nodes_;
  unsigned int current_node_;
};


} // namespace hext


#endif // HEXT_MATCHCONTEXT_H_INCLUDED

