#ifndef HEXT_PATTERN_BUILTIN_MATCH_H_INCLUDED
#define HEXT_PATTERN_BUILTIN_MATCH_H_INCLUDED

#include "hext/test/ValueTest.h"
#include "hext/pattern/ValueMatch.h"
#include "hext/Builtins.h"

#include <string>
#include <memory>

#include <gumbo.h>


namespace hext {


/// A BuiltinMatch is a ValueMatch that matches if the result of applying a
/// builtin function to an html-node passes `value_test`.
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
    std::unique_ptr<test::ValueTest> value_test
  );

  /// Return true if the result of applying `func` to node passes `value_test`,
  /// false otherwise.
  bool matches(const GumboNode * node) const final;

private:
  /// A pointer to a builtin function that is to be applied to a node.
  const BuiltinFuncPtr func_;
};


} // namespace hext


#endif // HEXT_PATTERN_BUILTIN_MATCH_H_INCLUDED

