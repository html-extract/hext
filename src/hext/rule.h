#ifndef HEXT_RULE_H
#define HEXT_RULE_H

#include <string>
#include <vector>
#include <memory>
#include <atomic>

#include <gumbo.h>

#include "hext/make-unique.h"
#include "hext/rule-patterns.h"
#include "hext/pattern/match-pattern.h"
#include "hext/pattern/capture-pattern.h"


namespace hext {


class MatchTree;

/// A Rule represents a source line from the hext input.
/// Generally: <direct_descendant?nth_child?tag_name? rule_pattern*>
///   Example: <!2div id="container" class="list">
///
/// tag_name represents the html-tag that we want to match. Empty tag_name
/// matches any html-tag.
/// A Rule matches an html-node if all RulePatterns are matched. Then,
/// RulePatterns extracts captured content which will be stored in a
/// MatchTree.
/// A Rule is a self-managing tree: each Rule has a vector of unique_ptr to
/// child-rule.
class Rule
{
public:
  Rule(
    const std::string& html_tag_name,
    bool is_optional,
    bool direct_descendant,
    bool closed,
    unsigned int nth_child,
    RulePatterns&& r_patterns
  );
  ~Rule();
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
  void append_child(Rule&& r, int level = 1);

  const std::vector<Rule>& children() const;
  std::string tag_name() const;
  bool optional() const;

  /// Recursively try to find and capture matches.
  void extract(const GumboNode * node, MatchTree * m) const;

  /// Recursively print the Rule and its child-rules, including rule-patterns
  /// and tag-name.
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
  /// A Rule matches when each match-pattern is found in the GumboNode and
  /// tag-name is equal (if non empty).
  bool matches(const GumboNode * node) const;

  /// Helper method that calls Rule::extract for each child of GumboNode.
  void extract_node_children(const GumboNode * node, MatchTree * m) const;

  /// Get the position of node within its parent. Only counts nodes of type
  /// GUMBO_NODE_ELEMENT. First node has position 1. Returns 0 if no parent.
  unsigned int get_node_position_within_parent(const GumboNode * node) const;

  std::vector<Rule> children_;
  RulePatterns patterns_;

  /// Count how often this Rule was matched.
  /// match_count is mutable because it is not observable from the outside.
  /// This enables us to keep Rule::match const.
  /// It is generally assumed that const objects are thread-safe,
  /// therefore mutable members must be made thread-safe.
  /// This is solved by using std::atomic.
  mutable std::atomic<unsigned int> match_count_;

  const GumboTag gumbo_tag_;
  const std::string tag_;
  const bool is_opt_;
  const bool is_direct_desc_;
  const bool is_closed_;
  const unsigned int child_pos_;
}; 


} // namespace hext


#endif // HEXT_RULE_H

