#ifndef HEXT_RULE_H
#define HEXT_RULE_H

#include <string>
#include <vector>
#include <memory>
#include <atomic>

#include <gumbo.h>

#include "hext/make-unique.h"
#include "hext/attribute.h"


namespace hext {


class match_tree;

/// A rule represents a source line from the hext input.
/// Generally: <direct_descendant?tag_name? attribute*>
///   Example: <!div id="container" class="list">
///
/// tag_name represents the html-tag that we want to match. Empty tag_name
/// matches any html-tag.
/// A rule's attributes can be matched against an html-tag and capture values
/// to be used in the result (match_tree).
/// A rule is a tree: each rule has a vector of child-rules.
class rule
{
public:
  rule(
    const std::string& html_tag_name,
    bool direct_descendant,
    int max_capture_limit,
    std::vector<attribute>&& attrs
  );

  /// Copy constructor. Resets match_count to zero.
  rule(const rule& r);

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
  void append_child(const rule& r, int level = 1);

  std::vector<rule>::size_type children_size() const;
  std::string tag_name() const;
  bool is_direct_descendant() const;
  int capture_limit() const;

  /// Recursively try to find and capture matches.
  /// Call this->matches(node):
  /// * if true, capture contents and append them to the match_tree.
  ///   Then call each child-rule's rule::match, for each child of node
  /// * if false, call this->match for each child of node.
  void match(const GumboNode * node, match_tree * m) const;

  /// Recursively print the rule and its child-rules, including attributes
  /// and tag-name.
  void print(std::ostream& out = std::cout, int indent_level = 0) const;

private:
  rule& operator=(const rule&) = delete;

  /// Capture attributes from a single GumboNode.
  /// Returns a single match_tree.
  std::unique_ptr<match_tree> capture(const GumboNode * node) const;

  /// Check wheter this rule matches a single GumboNode.
  /// A rule matches when each attribute is found in the GumboNode and
  /// tag-name is equal (if non empty).
  bool matches(const GumboNode * node) const;

  /// Helper method that calls rule::match for each child of GumboNode.
  void match_node_children(const GumboNode * node, match_tree * m) const;

  std::vector<rule> children;
  const std::vector<attribute> attributes;

  const std::string tag;
  const bool is_direct_desc;
  const int cap_limit;

  /// Count how often this rule was matched.
  /// match_count is mutable because it is not observable from the outside.
  /// This enables us to keep rule::match const.
  /// It is generally assumed that const objects are thread-safe,
  /// therefore mutable members must be made thread-safe.
  /// This is solved by using std::atomic.
  mutable std::atomic<int> match_count;
}; 


} // namespace hext


#endif // HEXT_RULE_H

