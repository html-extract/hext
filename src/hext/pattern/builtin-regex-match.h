#ifndef HEXT_BUILTIN_REGEX_MATCH_H
#define HEXT_BUILTIN_REGEX_MATCH_H

#include <string>
#include <iostream>

#include <gumbo.h>
#include <boost/regex.hpp>

#include "hext/builtins.h"
#include "hext/pattern/attribute-match.h"


namespace hext {


/// A builtin_regex_match is a match_pattern that matches if its builtin
/// function returns a string that matches regex.
class builtin_regex_match : public match_pattern
{
public:
  builtin_regex_match(bi::builtin_func_ptr f, const std::string& regex);
  match_result matches(const GumboNode * node) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  const bi::builtin_func_ptr func;
  const boost::regex rx;
};


} // namespace hext


#endif // HEXT_BUILTIN_REGEX_MATCH_H

