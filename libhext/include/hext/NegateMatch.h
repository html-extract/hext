#ifndef HEXT_NEGATE_MATCH_H_INCLUDED
#define HEXT_NEGATE_MATCH_H_INCLUDED

/// @file
///   Declares hext::NegateMatch

#include "hext/Match.h"

#include <memory>
#include <vector>

#include <gumbo.h>


namespace hext {


/// Matches HTML nodes for which every given Match returns false.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   GumboNode * attr_none = ...; // <hr/>
///   GumboNode * attr_one  = ...; // <h1 class="main-heading"></h1>
///   GumboNode * attr_two  = ...; // <div id="cart" class="my-cart"></div>
///
///   NegateMatch not_one (std::make_unique<AttributeCountMatch>(1));
///   NegateMatch not_none(std::make_unique<AttributeCountMatch>(0));
///
///   assert(!not_none.matches(attr_none));
///   assert( not_none.matches(attr_one));
///   assert( not_none.matches(attr_two));
///
///   assert( not_one.matches(attr_none));
///   assert(!not_one.matches(attr_one));
///   assert( not_one.matches(attr_two));
/// ~~~~~~~~~~~~~
class NegateMatch : public Match
{
public:
  /// Constructs a NegateMatch that matches nodes for which every contained
  /// Match returns false.
  ///
  /// @param v_matches:  An optional vector containing Matches.
  explicit
  NegateMatch(std::vector<std::unique_ptr<Match>>&& v_matches = {}) noexcept;

  /// Constructs a NegateMatch and appends a Match.
  ///
  /// @param match:  The Match to append.
  explicit NegateMatch(std::unique_ptr<Match>&& match);

  /// Appends a Match.
  ///
  /// @param match:  The Match to append.
  void take_match(std::unique_ptr<Match>&& match);

  /// Returns true if every contained Match returns false for node.
  ///
  /// @param node:  A pointer to a GumboNode.
  bool matches(const GumboNode * node) const final;

private:
  /// A vector containing Matches whose result will be negated.
  std::vector<std::unique_ptr<Match>> matches_;
};


} // namespace hext


#endif // HEXT_NEGATE_MATCH_H_INCLUDED

