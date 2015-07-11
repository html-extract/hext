#ifndef HEXT_MATCH_H_INCLUDED
#define HEXT_MATCH_H_INCLUDED

#include <gumbo.h>


namespace hext {


/// Match is the abstract base for all Matches that can be applied to
/// html-nodes.
class Match
{
public:
  /// Virtual destructor to allow inheritance.
  virtual ~Match() {}

  /// Implemenation must be provided in subclasses.
  virtual bool matches(const GumboNode * node) const = 0;
};


} // namespace hext


#endif // HEXT_MATCH_H_INCLUDED

