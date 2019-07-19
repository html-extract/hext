// Copyright 2015, 2016 Thomas Trapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef HEXT_NEGATE_MATCH_H_INCLUDED
#define HEXT_NEGATE_MATCH_H_INCLUDED

/// @file
///   Declares hext::NegateMatch

#include "hext/Cloneable.h"
#include "hext/Match.h"
#include "hext/Visibility.h"

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
class HEXT_PUBLIC NegateMatch final : public Cloneable<NegateMatch, Match>
{
public:
  /// Constructs a NegateMatch that matches nodes for which every contained
  /// Match returns false.
  ///
  /// @param v_matches:  An optional vector containing Matches.
  explicit
  NegateMatch(std::vector<std::unique_ptr<Match>> v_matches = {}) noexcept;

  /// Constructs a NegateMatch and appends a Match.
  ///
  /// @param match:  The Match to append.
  explicit NegateMatch(std::unique_ptr<Match> match);

  ~NegateMatch() noexcept override = default;
  NegateMatch(NegateMatch&& other) noexcept = default;
  NegateMatch(const NegateMatch& other);
  NegateMatch& operator=(NegateMatch&& other) noexcept = default;
  NegateMatch& operator=(const NegateMatch& other);

  /// Appends a Match.
  ///
  /// @param match:  The Match to append.
  void append_match(std::unique_ptr<Match> match);

  /// Returns true if every contained Match returns false for node.
  ///
  /// @param node:  A pointer to a GumboNode.
  bool matches(const GumboNode * node) const override;

private:
  /// A vector containing Matches whose result will be negated.
  std::vector<std::unique_ptr<Match>> matches_;
};


} // namespace hext


#endif // HEXT_NEGATE_MATCH_H_INCLUDED

