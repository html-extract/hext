#ifndef HEXT_PATTERN_MATCH_PATTERN_H_INCLUDED
#define HEXT_PATTERN_MATCH_PATTERN_H_INCLUDED

#include "hext/pattern/ValueTest.h"

#include <string>
#include <utility>
#include <memory>

#include <gumbo.h>


namespace hext {


/// A MatchResult contains a bool signaling whether the match was successful,
/// and, if applicable, a pointer to the GumboAttribute that was matched.
typedef std::pair<bool, const GumboAttribute *> MatchResult;

/// MatchPattern is the abstract base for all patterns that can be matched
/// against html-nodes.
class MatchPattern
{
public:
  /// Virtual destructor to allow inheriting.
  virtual ~MatchPattern();

  /// Implemenation must be provided in subclasses.
  virtual MatchResult matches(const GumboNode * node) const = 0;
};


} // namespace hext


#endif // HEXT_PATTERN_MATCH_PATTERN_H_INCLUDED

