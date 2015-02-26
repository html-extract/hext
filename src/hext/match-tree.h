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
  /// Convenience typedef for name-value-pairs. First member is the name of a
  /// capture, the second member is the value of a capture.
  typedef
    std::pair<std::string, std::string>
    NameValuePair;

  MatchTree();

  /// Append and own branch. Return a pointer to the new branch.
  MatchTree * append_child_and_own(std::unique_ptr<MatchTree> m);

  /// Append a NameValuePair to this branch.
  void append_match(const NameValuePair& p);

  /// Set the Rule that caused this MatchTree branch.
  void set_rule(const Rule * matching_rule);

  /// Print the MatchTree as json.
  /// Each child of the root of the MatchTree will form its own json object.
  void print_json(std::ostream& out = std::cout) const;

  /// Print the MatchTree as DOT, a graph description language.
  /// See http://en.wikipedia.org/wiki/DOT_language
  void print_dot(std::ostream& out = std::cout) const;

  /// Remove all nodes that do not conform to the rule tree,
  /// leaving a clean MatchTree with only valid results.
  /// When recursively matching GumboNodes in Rule::extract we do not want to
  /// care about wether a match will eventually be valid. Dropping invalid
  /// matches is much easier after we have processed all input.
  /// Do not remove optional Rules.
  /// Returns true on empty MatchTree.
  bool filter();

private:
  MatchTree(const MatchTree&) = delete;
  MatchTree& operator=(const MatchTree&) = delete;

  /// Recursively append all branches to the json document.
  void append_json_recursive(rapidjson::Document& json) const;

  /// Append a MatchTree's branch NameValuePairs to the json document.
  /// If a name already exists it is converted to an array and the new value is
  /// appended.
  ///
  /// For example, consider the key "Silvio" already being taken:
  ///   {"Silvio": "silver"}
  ///   then append_json_matches is called, with a branch
  ///   containing NameValuePair("Silvio", "gold")
  /// Produces:
  ///   {"Silvio": ["silver", "gold"]}
  void append_json_matches(rapidjson::Document& json) const;

  /// Recursivley print all DOT nodes. Each node has a distinct id. The
  /// parameter parent_id is neccessary to allow kids to connect to their
  /// parents.
  void print_dot_nodes(std::ostream& out, int parent_id = 0) const;

  /// MatchTrees are self-managing: all nodes are owned by the tree.
  std::vector<std::unique_ptr<MatchTree>> children_;

  /// The values captured by extracting.
  std::vector<NameValuePair> matches_;

  /// The Rule that caused this match.
  const Rule * r_;
};


} // namespace hext


#endif // HEXT_MATCH_TREE_H

