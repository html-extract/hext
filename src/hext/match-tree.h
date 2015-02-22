#ifndef HEXT_MATCH_TREE_H
#define HEXT_MATCH_TREE_H

#include <cassert>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


namespace hext {


class Rule;

/// A MatchTree contains the result of matching a Rule to GumboNodes through
/// Rule::extract().
class MatchTree
{
public:
  typedef
    std::pair<std::string, std::string>
    NameValuePair;

  MatchTree();

  MatchTree * append_child_and_own(std::unique_ptr<MatchTree> m);
  void append_match(const NameValuePair& p);
  void set_rule(const Rule * matching_rule);

  /// Print the MatchTree as json.
  /// Each child of the root of the MatchTree will form its own json object.
  void print_json(std::ostream& out = std::cout) const;

  /// Print the MatchTree as DOT, a graph description language.
  /// See http://en.wikipedia.org/wiki/DOT_language
  void print_dot(std::ostream& out = std::cout) const;

  /// Remove all nodes that do not conform to the rule tree,
  /// leaving a clean MatchTree with only valid results.
  /// When recursively matching GumboNodes in Rule::match we do not want to
  /// care about wether a match will eventually be valid. Dropping invalid
  /// matches is much easier after we have processed all input.
  /// Returns true on empty MatchTree.
  bool filter();

private:
  MatchTree(const MatchTree&) = delete;
  MatchTree& operator=(const MatchTree&) = delete;

  void append_json_recursive(rapidjson::Document& json) const;
  void append_json_matches(rapidjson::Document& json) const;
  void print_dot_nodes(std::ostream& out, int parent_id = 0) const;

  /// MatchTrees are self-managing: all nodes are owned by the tree
  std::vector<std::unique_ptr<MatchTree>> children_;

  /// The values captured by matching
  std::vector<NameValuePair> matches_;

  /// The Rule that caused this match
  const Rule * r_;
};


} // namespace hext


#endif // HEXT_MATCH_TREE_H

