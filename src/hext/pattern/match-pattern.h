#ifndef HEXT_MATCH_PATTERN_H
#define HEXT_MATCH_PATTERN_H

#include <string>
#include <iostream>
#include <utility>
#include <memory>

#include <gumbo.h>

#include "hext/pattern/attr-test.h"


namespace hext {


/// A MatchResult contains a bool deciding whether the match was successful,
/// and, if applicable, the GumboAttribute that was matched.
typedef std::pair<bool, const GumboAttribute *> MatchResult;

/// MatchPattern is an abstract base for all patterns that are used to check
/// whether an html-node is matched by a rule. Rules have MatchPatterns.
class MatchPattern
{
public:
  explicit MatchPattern(std::unique_ptr<AttrTest> attribute_test);
  virtual ~MatchPattern();
  virtual MatchResult matches(const GumboNode * node) const = 0;
  virtual void print(std::ostream& out = std::cout) const = 0;

protected:
  const std::unique_ptr<AttrTest> test_;
};


} // namespace hext


#endif // HEXT_MATCH_PATTERN_H

