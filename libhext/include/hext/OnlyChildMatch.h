#ifndef HEXT_ONLY_CHILD_MATCH_H_INCLUDED
#define HEXT_ONLY_CHILD_MATCH_H_INCLUDED

/// @file
///   Declares hext::OnlyChildMatch

#include "hext/HtmlTag.h"
#include "hext/Match.h"

#include <gumbo.h>


namespace hext {


/// Matches HTML nodes that are the only child of their parent HTML element.
///
/// The intent is to mimic the CSS pseudo-classes only-child and
/// only-child-of-type.
///
/// See https://developer.mozilla.org/en-US/docs/Web/CSS/:only-child
class OnlyChildMatch : public Match
{
public:
  /// OnlyChildMatch's options.
  enum Option
  {
    /// Count siblings of any type (:only-child).
    AnyType = 1 << 1,

    /// Only count siblings of the same type (:only-child-of-type).
    OfType  = 1 << 2
  };

  /// Constructs an OnlyChildMatch.
  ///
  /// @param options:  See OnlyChildMatch::Option.
  ///                  Default: Count any element (:only-child).
  explicit OnlyChildMatch(Option options = Option::AnyType);

  /// Returns true if node is the only child of its parent.
  bool matches(const GumboNode * node) const noexcept final;

private:
  /// See OnlyChildMatch::Option.
  Option options_;
};


/// Applies Bitwise-OR to OnlyChildMatch::Option.
inline OnlyChildMatch::Option
operator|(OnlyChildMatch::Option left, OnlyChildMatch::Option right) noexcept
{
  return static_cast<OnlyChildMatch::Option>(
    static_cast<int>(left) | static_cast<int>(right)
  );
}

/// Applies Bitwise-AND to OnlyChildMatch::Option.
inline OnlyChildMatch::Option
operator&(OnlyChildMatch::Option left, OnlyChildMatch::Option right) noexcept
{
  return static_cast<OnlyChildMatch::Option>(
    static_cast<int>(left) & static_cast<int>(right)
  );
}


} // namespace hext


#endif // HEXT_ONLY_CHILD_MATCH_H_INCLUDED

