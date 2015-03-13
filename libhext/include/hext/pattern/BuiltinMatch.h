#ifndef HEXT_PATTERN_BUILTIN_MATCH_H_INCLUDED
#define HEXT_PATTERN_BUILTIN_MATCH_H_INCLUDED

#include "hext/pattern/MatchPattern.h"
#include "hext/Builtins.h"

#include <string>
#include <iostream>
#include <memory>

#include <gumbo.h>


namespace hext {


/// A BuiltinMatch is a MatchPattern that checks whether the result of a
/// builtin matches value_test.
class BuiltinMatch : public MatchPattern
{
public:
  BuiltinMatch(
    BuiltinFuncPtr f,
    std::unique_ptr<ValueTest> value_test
  );

  MatchResult matches(const GumboNode * node) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  const BuiltinFuncPtr func_;
};


} // namespace hext


#endif // HEXT_PATTERN_BUILTIN_MATCH_H_INCLUDED

