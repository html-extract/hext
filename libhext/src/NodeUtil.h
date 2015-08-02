#ifndef HEXT_NODE_UTIL_H_INCLUDED
#define HEXT_NODE_UTIL_H_INCLUDED

#include "StringUtil.h"

#include <cassert>
#include <string>
#include <cstddef>
#include <iterator>

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


/// Returns inner HTML of an HTML node, as is, untouched.
std::string NodeInnerHtml(const GumboNode * node);


/// Returns true if an HTML tag is a tag for an element that is to be embedded
/// in newlines when converting HTML to text (that excludes most inline
/// elements, e.g. `<span>`).
bool TagWrapsText(GumboTag tag) noexcept;


/// Returns the next sibling of node.
const GumboNode * NextNode(const GumboNode * node) noexcept;


} // namespace hext


#endif // HEXT_NODE_UTIL_H_INCLUDED

