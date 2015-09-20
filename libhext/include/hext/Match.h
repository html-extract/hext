#ifndef HEXT_MATCH_H_INCLUDED
#define HEXT_MATCH_H_INCLUDED

/// @file
///   Declares hext::Match

#include <memory>

#include <gumbo.h>


namespace hext {


/// Abstract base for every Match.
///
/// Matches are applied to HTML nodes with Match::matches() which will
/// return true if the HTML node matches.
///
/// Note: You probably don't want to inherit from this class directly, unless
///       you want to provide your own Match::clone() method. If your subclass
///       has a copy constructor, you can extend from
///       hext::Cloneable<YourSubclass, hext::Match> which provides a generic
///       clone method.
class Match
{
public:
  // Rule of five
  Match() = default;
  Match(const Match&) = default;
  Match(Match&&) = default;
  Match& operator=(const Match&) = default;
  Match& operator=(Match&&) = default;
  virtual ~Match() = default;

  /// Clones derived object.
  virtual std::unique_ptr<Match> clone() const = 0;

  /// Returns true if this Match matches node.
  virtual bool matches(const GumboNode * node) const = 0;
};


} // namespace hext


#endif // HEXT_MATCH_H_INCLUDED

