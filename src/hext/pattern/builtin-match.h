#ifndef HEXT_BUILTIN_MATCH_H
#define HEXT_BUILTIN_MATCH_H

#include <string>
#include <iostream>
#include <memory>

#include <gumbo.h>

#include "hext/pattern/match-pattern.h"
#include "hext/builtins.h"


namespace hext {


class BuiltinMatch : public MatchPattern
{
public:
  BuiltinMatch(
    bi::BuiltinFuncPtr f,
    std::unique_ptr<AttrTest> attribute_test
  );

  MatchResult matches(const GumboNode * node) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  const bi::BuiltinFuncPtr func;
};


} // namespace hext


#endif // HEXT_BUILTIN_MATCH_H

