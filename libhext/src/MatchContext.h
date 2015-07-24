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
  typedef std::vector<Rule>::const_iterator rule_it;

  MatchContext(rule_it            rule_begin,
               rule_it            rule_end,
               const GumboVector& nodes) noexcept;

  /// Return next match_group. Return empty if there are no more matches.
  boost::optional<match_group> match_next();

private:
  /// Return first mandatory rule. Searches range [it, this->r_end_) followed by
  /// [this->r_begin_, it).
  /// Return this->r_end_ if there are no mandatory rules.
  rule_it find_mandatory_rule(rule_it it) const noexcept;

  /// Return node index for the first node in [begin, end) that matches rule.
  /// Return end if no match.
  unsigned int find_match(unsigned int begin,
                          unsigned int end,
                          const Rule&  rule) const;

  /// Match rules in range [rule, stop_rule) until all rules where matched or
  /// stop_node is encountered. Modifies this->n_ to point to one after the
  /// last matching node. Pushes all matches into match_group mg.
  void match_to_node(match_group& mg,
                     rule_it      rule,
                     rule_it      stop_rule,
                     unsigned int stop_node);

  /// Push rule and node into match_group mg. Convenience helper to avoid
  /// littering the code with casts.
  void push_match_pair(match_group& mg, rule_it rule, unsigned int n) const;

  rule_it r_begin_;
  rule_it r_end_;

  const GumboVector& nodes_;
  /// Current index within this->nodes_
  unsigned int n_;
  unsigned int n_len_;
};


} // namespace hext


#endif // HEXT_MATCHCONTEXT_H_INCLUDED

