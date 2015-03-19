#ifndef HEXT_PATTERN_MATCH_PATTERN_H_INCLUDED
#define HEXT_PATTERN_MATCH_PATTERN_H_INCLUDED

#include "hext/pattern/ValueTest.h"

#include <string>
#include <utility>
#include <memory>

#include <gumbo.h>


namespace hext {


/// A MatchResult contains a bool deciding whether the match was successful,
/// and, if applicable, the GumboAttribute that was matched.
typedef std::pair<bool, const GumboAttribute *> MatchResult;

/// MatchPattern is an abstract base for all patterns that are used to check
/// whether an html-node is matched by a rule. Rules have MatchPatterns.
class MatchPattern
{
public:
  MatchPattern();
  virtual ~MatchPattern();
  virtual MatchResult matches(const GumboNode * node) const = 0;
};


} // namespace hext


#endif // HEXT_PATTERN_MATCH_PATTERN_H_INCLUDED

