#ifndef HEXT_RESULT_TREE_H_INCLUDED
#define HEXT_RESULT_TREE_H_INCLUDED

#include "hext/Result.h"

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <algorithm>
#include <map>


namespace hext {


/// Forward declare Rule because it depends on ResultTree.
class Rule;

/// A ResultTree contains the result of matching a Rule to GumboNodes through
/// `Rule::extract()`.
class ResultTree
{
public:
  /// Convenience typedef for name-value-pairs. First member is the name of a
  /// capture, the second member is the value of a capture.
  typedef
    std::pair<std::string, std::string>
    NameValuePair;

  /// Construct a ResultTree.
  /// \param rule
  ///     The rule that caused the creation of this ResultTree.
  explicit ResultTree(const Rule * rule);

  /// Construct a ResultTree with values.
  /// \param rule
  ///     The rule that caused the creation of this ResultTree.
  /// \param values
  ///     Values for this ResultTree branch.
  ResultTree(const Rule * rule, std::vector<NameValuePair> values);

  ResultTree(ResultTree&&) = default;

  /// Create a new branch. Return a non-owning pointer to the new branch.
  /// \param rule
  ///     The rule that caused the creation of this ResultTree.
  /// \param values
  ///     Values for the new ResultTree branch.
  ResultTree * create_branch(
    const Rule * rule,
    std::vector<NameValuePair> values
  );

  /// Remove incomplete branches. An incomplete branch occurs if a Rule matches
  /// an html-subtree, but its Rule siblings or children do not match.
  /// Branches that were created by optional Rules are not removed.
  /// Always returns false.
  bool filter();

  /// Return a vector containing multimaps of string pairs. Each element in the
  /// vector represents a child of this ResultTree. The multimaps are the result
  /// of recursively appending each subtree, flattening all values to a single
  /// map.
  /// Note: Values from this instance are omitted.
  Result to_result() const;

private:
  ResultTree(const ResultTree&) = delete;
  ResultTree& operator=(const ResultTree&) = delete;

  /// Recursively insert all `values_` into `map`, including this instance's
  /// `values_`.
  void save(ResultMap& map) const;

  /// ResultTrees are self-managing: all nodes are owned by the tree.
  std::vector<std::unique_ptr<ResultTree>> children_;

  /// The values captured by extracting.
  const std::vector<NameValuePair> values_;

  /// The Rule that produced this ResultTree.
  const Rule * const matching_rule_;
};


} // namespace hext


#endif // HEXT_RESULT_TREE_H_INCLUDED

