#ifndef HEXT_MATCHCONTEXT_H_INCLUDED
#define HEXT_MATCHCONTEXT_H_INCLUDED

#include <utility>
#include <vector>
#include <cstddef>

#include <boost/optional.hpp>
#include <gumbo.h>


namespace hext {


class Rule;


/// Matches a group of rules against a GumboVector of nodes.
class MatchContext
{
public:
  typedef std::vector<std::pair<const Rule *, const GumboNode *>> match_group;
  typedef std::vector<Rule>::const_iterator rule_it;

  /// Constructs a MatchContext.
  ///
  /// @param rule_begin:  The beginning of a range of Rule.
  /// @param   rule_end:  The end of a range of Rule.
  /// @param      nodes:  A GumboVector of nodes.
  MatchContext(rule_it            rule_begin,
               rule_it            rule_end,
               const GumboVector& nodes) noexcept;

  /// Returns the next match_group.
  /// Returns empty if there are no more matches.
  boost::optional<match_group> match_next();

private:
  /// Returns first mandatory rule. Searches range [it, this->r_end_) followed by
  /// [this->r_begin_, it).
  /// Returns this->r_end_ if there are no mandatory rules.
  ///
  /// @param it:  The iterator at which to start searching.
  rule_it find_mandatory_rule(rule_it it) const noexcept;

  /// Returns the node index for the first node in [begin, end) that matches
  /// rule.
  /// Returns end if no match.
  ///
  /// @param begin:  The index of a node in this->nodes_ where to start matching.
  /// @param   end:  The index of a node in this->nodes_ where to stop matching.
  /// @param  rule:  The rule that is to be matched against nodes.
  unsigned int find_match(unsigned int begin,
                          unsigned int end,
                          const Rule&  rule) const;

  /// Matches rules in range [rule, stop_rule) until all rules were matched or
  /// stop_node is encountered. Modifies this->n_ to point to one after the
  /// last matching node. Pushes all matches into match_group mg.
  ///
  /// @param        mg: The match_group in which to insert all matches.
  /// @param      rule: The beginning of a range of Rule.
  /// @param      rule: The end of a range of Rule.
  /// @param stop_node: The end of the range of nodes that are to be
  ///                   matched, i.e. [this->nodes_, stop_node).
  void match_to_node(match_group& mg,
                     rule_it      rule,
                     rule_it      stop_rule,
                     unsigned int stop_node);

  /// Convenience method that pushes rule and node into match_group mg.
  ///
  /// @param   mg: The match_group in which to insert.
  /// @param rule: The matching rule.
  /// @param    n: The index of the matching node.
  void push_match_pair(match_group& mg, rule_it rule, unsigned int n) const;

  /// The beginning of a range of Rule given in the constructor.
  rule_it r_begin_;

  /// The end of a range of Rule given in the constructor.
  rule_it r_end_;

  /// The GumboVector of nodes given in the constructor.
  const GumboVector& nodes_;

  /// Current index within this->nodes_. Successive calls to
  /// MatchContext::match_next() will update n_ until n_len_ is reached.
  unsigned int n_;

  /// The length of this->nodes_ as given in the constructor.
  unsigned int n_len_;
};


} // namespace hext


#endif // HEXT_MATCHCONTEXT_H_INCLUDED

