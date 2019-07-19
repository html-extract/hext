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

#ifndef HEXT_ATTRIBUTE_MATCH_H_INCLUDED
#define HEXT_ATTRIBUTE_MATCH_H_INCLUDED

/// @file
///   Declares hext::AttributeMatch

#include "hext/Cloneable.h"
#include "hext/Match.h"
#include "hext/ValueTest.h"
#include "hext/Visibility.h"

#include <memory>
#include <string>

#include <gumbo.h>


namespace hext {


/// Matches HTML elements having an HTML attribute with a certain name
/// and, optionally, whose value is matched by a ValueTest.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   GumboNode * node_row        = ...; // <td data-row=""></td>
///   GumboNode * node_desolation = ...; // <td data-row="desolation"></td>
///
///   // Match nodes containing an attribute called data-row
///   AttributeMatch attr_row(
///     "data-row"  // attribute name
///   );
///   attr_row.matches(node_row);
///   attr_row.matches(node_desolation);
///
///   // Match nodes containing an attribute called data-row whose value equals
///   // "desolation"
///   AttributeMatch attr_desolation(
///     "data-row",                                 // attribute name
///     std::make_unique<EqualsTest>("desolation")  // ValueTest
///   );
///   assert(attr_desolation.matches(node_desolation));
///   assert(!attr_desolation.matches(node_row));
/// ~~~~~~~~~~~~~
class HEXT_PUBLIC AttributeMatch final : public Cloneable<AttributeMatch, Match>
{
public:
  /// Constructs an AttributeMatch with an optional ValueTest.
  ///
  /// @param attr_name:   The name of the HTML attribute.
  /// @param value_test:  An optional ValueTest which, if given, must return
  ///                     true for the matched HTML attribute's value.
  explicit AttributeMatch(std::string                attr_name,
                          std::unique_ptr<ValueTest> value_test = {}) noexcept;

  ~AttributeMatch() noexcept override = default;
  AttributeMatch(AttributeMatch&& other) noexcept = default;
  AttributeMatch(const AttributeMatch& other);
  AttributeMatch& operator=(AttributeMatch&& other) noexcept = default;
  AttributeMatch& operator=(const AttributeMatch& other);

  /// Return true if node has an HTML attribute called attr_name (as given in
  /// the constructor). If a ValueTest was supplied, the ValueTest must return
  /// true for the attribute's value.
  ///
  /// @param node:  A pointer to a GumboNode of type GUMBO_NODE_ELEMENT.
  bool matches(const GumboNode * node) const override;

private:
  /// The name of the HTML attribute.
  std::string attr_name_;

  /// An optional ValueTest that, if not null, will be applied to the HTML
  /// attribute's value.
  std::unique_ptr<ValueTest> test_;
};


} // namespace hext


#endif // HEXT_ATTRIBUTE_MATCH_H_INCLUDED

