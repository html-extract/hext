#ifndef HEXT_LITERAL_MATCH_H
#define HEXT_LITERAL_MATCH_H

#include <string>
#include <cstring>
#include <iostream>

#include <gumbo.h>

#include "hext/match-pattern.h"


namespace hext {


/// A literal_match is a match_pattern that checks whether an html-node has an
/// attribute called attr_name with a value that matches literal exactly.
class literal_match : public match_pattern
{
public:
  literal_match(const std::string& attr_name, const std::string& attr_value);
  /// Returns std::pair<false, nullptr> if GumboNode does not have any
  /// attribute called attr_name with exact value 'literal'.
  match_result matches(const GumboNode * node) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  const std::string literal;
};


} // namespace hext


#endif // HEXT_LITERAL_MATCH_H

