#ifndef HEXT_PATTERN_BUILTIN_MATCH_H_INCLUDED
#define HEXT_PATTERN_BUILTIN_MATCH_H_INCLUDED

#include "hext/pattern/ValueMatch.h"
#include "hext/Builtins.h"

#include <string>
#include <memory>

#include <gumbo.h>


namespace hext {


/// A BuiltinMatch is a MatchPattern that checks whether the result of a
/// builtin matches value_test. An BuiltinMatch is a ValueMatch that matches
/// if the result of applying a builtin function to an html-node passes
/// `value_test`.
class BuiltinMatch : public ValueMatch
{
public:
  /// Construct a BuiltinMatch.
  ///
  /// \param func
  ///     A pointer to a builtin function that is to be applied to a node.
  /// \param value_test
  ///     The ValueTest which is to be applied to the result of `func`.
  BuiltinMatch(
    BuiltinFuncPtr func,
    std::unique_ptr<ValueTest> value_test
  );

  /// Return a pair: First member is true if the result of applying `func`
  /// to node passes `value_test`, false otherwise. Second member is always
  /// a nullptr and can be ignored.
  MatchResult matches(const GumboNode * node) const final;

private:
  /// A pointer to a builtin function that is to be applied to a node.
  const BuiltinFuncPtr func_;
};


} // namespace hext


#endif // HEXT_PATTERN_BUILTIN_MATCH_H_INCLUDED

