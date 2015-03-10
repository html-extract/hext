#ifndef HEXT_RULE_H_INCLUDED
#define HEXT_RULE_H_INCLUDED

#include "hext/node-util.h"
#include "hext/make-unique.h"
#include "hext/rule-patterns.h"
#include "hext/pattern/match-pattern.h"
#include "hext/pattern/capture-pattern.h"

#include <string>
#include <vector>
#include <memory>
#include <atomic>

#include <gumbo.h>


namespace hext {


class ResultTree;

/// A Rule represents a source line from the hext input.
/// Generally: <is_optional?(dd|nth_child)?tag_name? rule_pattern*>
///   Example: <!2div id="container" class="list">
///
/// A Rule matches an html-node if all its attributes are satisfied:
///  * is_optional: Ignored while matching. When ResultTree::filter is called,
///    invalid ResultTree branches are removed, unless this flag is set.
///  * nth_child or direct_descendant: Matches if the node is a direct
///    descendant of its parent. If nth_child is given, it must match the index
///    within its parent node (the index is determined by ignoring text-nodes,
///    see node-util's GetNodePositionWithinParent)
///  * gumbo_tag: The tag_name of the rule, as parsed by gumbo. Matches if the
///    node's tag is the same. Set to GUMBO_TAG_UNKNOWN if any tag may match.
///  * RulePatterns: If the Rule is closed,
///    RulePatterns::matches_all_attributes() must return true. If the Rule is
///    not optional, RulePatterns::matches() must return true.
///
/// If a node matches a Rule, RulePatterns::capture() is called, which returns
/// a new ResultTree branch, containing all captured NameValuePairs.
///
/// A Rule is a tree: each Rule has a vector of child-rules.
class Rule
{
public:
  Rule(
    GumboTag gumbo_tag,
    bool is_optional,
    int nth_child,
    bool closed,
    RulePatterns&& r_patterns
  );

  /// Move constructor. We cannot use default generation, because std::atomic
  /// has no move support.
  Rule(Rule&& r);

  /// Append child-rule after last element at tree-level level.
  /// Example Rule:
  ///   level0  <div>       # this
  ///   level1    <li>
  ///   level2      <span>
  ///   level1    <li>
  ///   level2      <img>
  ///
  /// this->append_child(<a>, 2):
  ///   level0  <div>      # this
  ///   level1    <li>
  ///   level2      <span>
  ///   level1    <li>
  ///   level2      <img>
  ///   level2      <a>    # new
  ///
  /// Only used when constructing Rules in the parser.
  void append_child(Rule&& r, int level = 1);

  const std::vector<Rule>& children() const;
  GumboTag gumbo_tag() const;
  bool optional() const;

  /// Recursively try to find and capture matches.
  void extract(const GumboNode * node, ResultTree * r) const;

  /// Recursively print the Rule and its child-rules.
  /// If print_match_count is true, print a column containing the match count
  /// for each rule.
  void print(
    std::ostream& out = std::cout,
    int indent_level = 0,
    bool print_match_count = false
  ) const;

private:
  Rule(const Rule& r) = delete;
  Rule& operator=(Rule&&) = delete;
  Rule& operator=(const Rule&) = delete;

  /// Check wheter this Rule matches a single GumboNode.
  bool matches(const GumboNode * node) const;

  /// Helper method that calls Rule::extract for each child of GumboNode.
  void extract_node_children(const GumboNode * node, ResultTree * rt) const;

  std::vector<Rule> children_;
  RulePatterns patterns_;

  /// Count how often this Rule was matched.
  /// match_count is mutable because it is not observable from the outside.
  /// This enables us to keep Rule::extract const.
  /// It is generally assumed that const objects are thread-safe,
  /// therefore mutable members must be made thread-safe.
  /// This is solved by using std::atomic.
  mutable std::atomic<unsigned int> match_count_;

  const GumboTag gumbo_tag_;
  const bool is_optional_;
  const int nth_child_;
  const bool is_closed_;
}; 


} // namespace hext


#endif // HEXT_RULE_H_INCLUDED

