#ifndef HEXT_MATCH_H_INCLUDED
#define HEXT_MATCH_H_INCLUDED

/// @file
///   Declares hext::Match

#include <gumbo.h>


namespace hext {


/// Abstract base for every Match.
///
/// Matches are applied to HTML nodes with Match::matches() which will
/// return true if the HTML node matches.
class Match
{
public:
  /// Virtual destructor to allow inheritance.
  virtual ~Match();

  /// Implemenation must be provided in subclasses.
  virtual bool matches(const GumboNode * node) const = 0;
};


} // namespace hext


#endif // HEXT_MATCH_H_INCLUDED

