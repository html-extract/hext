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

#ifndef HEXT_FUNCTION_MATCH_H_INCLUDED
#define HEXT_FUNCTION_MATCH_H_INCLUDED

/// @file
///   Declares hext::FunctionMatch

#include "hext/Cloneable.h"
#include "hext/Match.h"
#include "hext/MatchFunction.h"
#include "hext/Visibility.h"

#include <gumbo.h>


namespace hext {


/// Matches if the result of applying a given MatchFunction to an HTML node
/// returns true.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   GumboNode * div  = ...; // <div>This is a div!</div>
///   GumboNode * span = ...; // <span>This is a span!</span>
///
///   MatchFunction is_div = [](const GumboNode * node) {
///     return node->type == GUMBO_NODE_ELEMENT &&
///            node->v.element.tag == GUMBO_TAG_DIV;
///   };
///
///   FunctionMatch m_is_div(is_div);
///
///   assert( m_is_div.matches(div));
///   assert(!m_is_div.matches(span));
/// ~~~~~~~~~~~~~
class HEXT_PUBLIC FunctionMatch final : public Cloneable<FunctionMatch, Match>
{
public:
  /// Constructs a FunctionMatch that matches HTML nodes for which a given
  /// MatchFunction returns true.
  ///
  /// @param func:  The MatchFunction that will be applied to an HTML
  ///               node.
  explicit FunctionMatch(MatchFunction func);

  /// Returns true if the result of calling the given MatchFunction with node
  /// as its first argument returns true.
  ///
  /// @param node:  The node which is to be matched.
  bool matches(const GumboNode * node) const override;

private:
  /// The MatchFunction that will be applied to an HTML node.
  MatchFunction func_;
};


} // namespace hext


#endif // HEXT_FUNCTION_MATCH_H_INCLUDED

