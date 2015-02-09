#ifndef HEXT_BUILTIN_LITERAL_MATCH_H
#define HEXT_BUILTIN_LITERAL_MATCH_H

#include <string>
#include <iostream>

#include <gumbo.h>

#include "hext/pattern/match-pattern.h"
#include "hext/builtins.h"


namespace hext {


/// A builtin_literal_match is a match_pattern that matches if its builtin
/// function returns a string that is equal to attr_value.
class builtin_literal_match : public match_pattern
{
public:
  builtin_literal_match(bi::builtin_func_ptr f, const std::string& attr_value);
  match_result matches(const GumboNode * node) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  const bi::builtin_func_ptr func;
  const std::string value;
};


} // namespace hext


#endif // HEXT_BUILTIN_LITERAL_MATCH_H

