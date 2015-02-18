#ifndef HEXT_BUILTIN_MATCH_H
#define HEXT_BUILTIN_MATCH_H

#include <string>
#include <iostream>
#include <memory>

#include <gumbo.h>

#include "hext/pattern/match-pattern.h"
#include "hext/builtins.h"


namespace hext {


class builtin_match : public match_pattern
{
public:
  builtin_match(
    bi::builtin_func_ptr f,
    std::unique_ptr<attr_test> attribute_test
  );

  match_result matches(const GumboNode * node) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  const bi::builtin_func_ptr func;
};


} // namespace hext


#endif // HEXT_BUILTIN_MATCH_H

