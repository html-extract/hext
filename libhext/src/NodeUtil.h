// Copyright 2015,2016 Thomas Trapp
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

#ifndef HEXT_NODE_UTIL_H_INCLUDED
#define HEXT_NODE_UTIL_H_INCLUDED

#include "StringUtil.h"

#include <sstream>
#include <string>

#include <gumbo.h>


namespace hext {


/// Returns inner text of an HTML node. Trims left and right whitespace and
/// collapses multiple whitespace into a single space.
std::string NodeText(const GumboNode * node);


/// Strips HTML tags of an HTML element. If smart_wrap is enabled, the content
/// of some elements is embedded in newlines. For example,
/// `This is<div>a</div>sentence.` becomes `This is\na\nsentence.`. If
/// smart_wrap is disabled, the result will be `This isasentence.`.
/// See implementation of TagWrapsText for a list of affected elements.
std::string StripTags(const GumboNode * node, bool smart_wrap = false);


/// Returns inner HTML of an HTML element.
std::string NodeInnerHtml(const GumboNode * node);


/// Serializes GumboNode to string and appends it to os.
void SerializeNode(const GumboNode& node, std::ostringstream& os);


/// Serializes GumboDocument to string and appends it to os.
void SerializeDocument(const GumboDocument& d, std::ostringstream& os);


/// Serializes GumboAttribute to string and appends it to os.
void SerializeAttribute(const GumboAttribute& a, std::ostringstream& os);


/// Serializes GumboElement to string and appends it to os.
void SerializeElement(const GumboElement& e, std::ostringstream& os);


/// Returns true if HTML tag is a tag for a "void element".
/// See https://www.w3.org/TR/html5/syntax.html#void-elements
bool TagIsSelfClosing(GumboTag tag) noexcept;


/// Returns true if an HTML tag is a tag for an element that is to be embedded
/// in newlines when converting HTML to text (that excludes most inline
/// elements, e.g. `<span>`).
bool TagWrapsText(GumboTag tag) noexcept;


/// Returns the next sibling of node.
const GumboNode * NextNode(const GumboNode * node) noexcept;


} // namespace hext


#endif // HEXT_NODE_UTIL_H_INCLUDED

