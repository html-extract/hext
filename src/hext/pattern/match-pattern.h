#ifndef HEXT_MATCH_PATTERN_H
#define HEXT_MATCH_PATTERN_H

#include <string>
#include <iostream>
#include <utility>
#include <memory>

#include <gumbo.h>

#include "hext/pattern/attr-test.h"


namespace hext {


/// A match_result contains a bool deciding whether the match was successful,
/// and, if applicable, the GumboAttribute that was matched.
typedef std::pair<bool, const GumboAttribute *> match_result;

/// match_pattern is an abstract base for all patterns that are used to check
/// whether an html-node is matched by a rule. Rules have match_patterns.
class match_pattern
{
public:
  explicit match_pattern(std::unique_ptr<attr_test> attribute_test);
  virtual match_result matches(const GumboNode * node) const = 0;
  virtual void print(std::ostream& out = std::cout) const = 0;
  virtual ~match_pattern();

protected:
  const std::unique_ptr<attr_test> test;
};


} // namespace hext


#endif // HEXT_MATCH_PATTERN_H

