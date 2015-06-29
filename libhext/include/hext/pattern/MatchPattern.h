#ifndef HEXT_PATTERN_MATCH_PATTERN_H_INCLUDED
#define HEXT_PATTERN_MATCH_PATTERN_H_INCLUDED

#include <gumbo.h>


namespace hext {


/// MatchPattern is the abstract base for all patterns that can be matched
/// against html-nodes.
class MatchPattern
{
public:
  /// Virtual destructor to allow inheritance.
  virtual ~MatchPattern()
    {}

  /// Implemenation must be provided in subclasses.
  virtual bool matches(const GumboNode * node) const = 0;
};


} // namespace hext


#endif // HEXT_PATTERN_MATCH_PATTERN_H_INCLUDED

