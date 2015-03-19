#ifndef HEXT_PATTERN_BUILTIN_MATCH_H_INCLUDED
#define HEXT_PATTERN_BUILTIN_MATCH_H_INCLUDED

#include "hext/pattern/ValueMatch.h"
#include "hext/Builtins.h"

#include <string>
#include <memory>

#include <gumbo.h>


namespace hext {


/// A BuiltinMatch is a MatchPattern that checks whether the result of a
/// builtin matches value_test.
class BuiltinMatch : public ValueMatch
{
public:
  BuiltinMatch(
    BuiltinFuncPtr f,
    std::unique_ptr<ValueTest> value_test
  );

  MatchResult matches(const GumboNode * node) const final;

private:
  const BuiltinFuncPtr func_;
};


} // namespace hext


#endif // HEXT_PATTERN_BUILTIN_MATCH_H_INCLUDED

