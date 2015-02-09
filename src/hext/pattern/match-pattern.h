#ifndef HEXT_MATCH_PATTERN_H
#define HEXT_MATCH_PATTERN_H

#include <string>
#include <iostream>
#include <utility>

#include <gumbo.h>


namespace hext {


/// A match_result contains a bool deciding whether the match was successful,
/// and, if applicable, the GumboAttribute that was matched.
typedef std::pair<bool, const GumboAttribute *> match_result;

/// match_pattern is an abstract base for all patterns that are used to check
/// whether an html-node is matched by a rule. Rules have match_patterns.
class match_pattern
{
public:
  match_pattern();
  virtual match_result matches(const GumboNode * node) const = 0;
  virtual void print(std::ostream& out = std::cout) const = 0;
  virtual ~match_pattern();
};


} // namespace hext


#endif // HEXT_MATCH_PATTERN_H

