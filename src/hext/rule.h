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


class match_tree;

/// A rule represents a source line from the hext input.
/// Generally: <direct_descendant?nth_child?tag_name? rule_pattern*>
///   Example: <!2div id="container" class="list">
///
/// tag_name represents the html-tag that we want to match. Empty tag_name
/// matches any html-tag.
/// A rule matches an html-node if all rule_patterns are matched. Then,
/// rule_patterns extracts captured content which will be stored in a
/// match_tree.
/// A rule is a self-managing tree: each rule has a vector of unique_ptr to
/// child-rule.
class rule
{
public:
  rule(
    const std::string& html_tag_name,
    bool direct_descendant,
    bool closed,
    unsigned int nth_child,
    rule_patterns&& r_patterns
  );

  rule(rule&& r);

  /// Append child-rule after last element at tree-level level.
  /// Example rule:
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
  void append_child(rule&& r, int level = 1);

  std::vector<rule>::size_type children_size() const;
  std::string tag_name() const;
  bool is_direct_descendant() const;

  /// Recursively try to find and capture matches.
  void extract(const GumboNode * node, match_tree * m) const;

  /// Recursively print the rule and its child-rules, including rule-patterns
  /// and tag-name.
  void print(
    std::ostream& out = std::cout,
    int indent_level = 0,
    bool print_match_count = false
  ) const;

private:
  rule(const rule& r) = delete;
  rule& operator=(rule&&) = delete;
  rule& operator=(const rule&) = delete;

  /// Check wheter this rule matches a single GumboNode.
  /// A rule matches when each match-pattern is found in the GumboNode and
  /// tag-name is equal (if non empty).
  bool matches(const GumboNode * node) const;

  /// Helper method that calls rule::extract for each child of GumboNode.
  void extract_node_children(const GumboNode * node, match_tree * m) const;

  /// Get the position of node within its parent. Only counts nodes of type
  /// GUMBO_NODE_ELEMENT. First node has position 1. Returns 0 if no parent.
  unsigned int get_node_position_within_parent(const GumboNode * node) const;

  std::vector<rule> children;
  rule_patterns patterns;

  /// Count how often this rule was matched.
  /// match_count is mutable because it is not observable from the outside.
  /// This enables us to keep rule::match const.
  /// It is generally assumed that const objects are thread-safe,
  /// therefore mutable members must be made thread-safe.
  /// This is solved by using std::atomic.
  mutable std::atomic<unsigned int> match_count;

  const std::string tag;
  const bool is_direct_desc;
  const bool is_closed;
  const unsigned int child_pos;
}; 


} // namespace hext


#endif // HEXT_RULE_H

