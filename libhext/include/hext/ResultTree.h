#ifndef HEXT_RESULT_TREE_H_INCLUDED
#define HEXT_RESULT_TREE_H_INCLUDED

#include "hext/Result.h"
#include "hext/MakeUnique.h"

#include <cassert>
#include <string>
#include <vector>
#include <memory>
#include <map>


namespace hext {


/// A ResultTree contains the result of matching a Rule to GumboNodes through
/// `Rule::extract()`.
class ResultTree
{
public:
  /// Construct a ResultTree with values.
  /// \param values
  ///     Values for this ResultTree branch.
  explicit ResultTree(
    std::vector<ResultPair> values = std::vector<ResultPair>()
  );

  ResultTree(ResultTree&&) = default;

  /// Create a new branch. Return a non-owning pointer to the new branch.
  /// \param values
  ///     Values for the new ResultTree branch.
  ResultTree * create_child(
    std::vector<ResultPair> values = std::vector<ResultPair>()
  );

  /// Delete a child branch pointed to by `child`. If `child` is not found
  /// nothing is done.
  void delete_child(const ResultTree * child);

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
  std::vector<ResultPair> values_;
};


} // namespace hext


#endif // HEXT_RESULT_TREE_H_INCLUDED

