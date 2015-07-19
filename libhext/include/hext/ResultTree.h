#ifndef HEXT_RESULT_TREE_H_INCLUDED
#define HEXT_RESULT_TREE_H_INCLUDED

#include "hext/Result.h"

#include <vector>
#include <memory>


namespace hext {


/// A self-managing tree containing all values captured from HTML.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   std::string hext_str(
///     "<a href={href}><img/></a>" // i.e. capture the attribute href from all
///                                 // anchor elements that have a child with
///                                 // HtmlTag <img>.
///   Parser p(hext_str.begin(), hext_str.end());
///   Rule rule = p.parse();
///   std::unique_ptr<ResultTree> rt = rule.extract([html]);
///   Result result = rt->flatten();
///   // Each element of result is an unordered multimap, each containing one
///   // string pair.
/// ~~~~~~~~~~~~~
class ResultTree
{
public:
  /// Constructs an empty ResultTree.
  ResultTree();

  ResultTree(ResultTree&&);
  ResultTree& operator=(ResultTree&&);
  ~ResultTree();

  /// Appends a new branch.
  ///
  /// @returns  A non-owning pointer to the newly created child.
  ResultTree * create_child();

  /// Deletes the child branch pointed to by child.
  ///
  /// @param child:  The child branch wich will be deleted. If it is not a child
  ///                of this instance, the call will have no effect.
  void delete_child(const ResultTree * child);

  /// Sets the captured values for this branch.
  ///
  /// @param v:  A vector containing string-pairs.
  void set_values(std::vector<ResultPair> v);

  /// Returns read-only access to the values of this tree node.
  const std::vector<ResultPair>& values() const;

  /// Returns read-only access to the children of this tree node.
  const std::vector<std::unique_ptr<ResultTree>>& children() const;

  /// Returns a vector<ResultMap> containing all values from all children.
  /// Each element of the vector represents a complete extraction done
  /// by a Rule.
  Result flatten() const;

private:
  ResultTree(const ResultTree&) = delete;
  ResultTree& operator=(const ResultTree&) = delete;

  struct Impl;
  std::unique_ptr<Impl> impl_;
};


} // namespace hext


#endif // HEXT_RESULT_TREE_H_INCLUDED

