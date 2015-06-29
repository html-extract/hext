#ifndef HEXT_NODE_UTIL_H_INCLUDED
#define HEXT_NODE_UTIL_H_INCLUDED

#include "hext/StringUtil.h"

#include <cassert>
#include <string>
#include <cstddef>
#include <iterator>

#include <gumbo.h>


namespace hext {


/// Get inner text of a `node`. Trim left and right whitespace and collapse
/// multiple whitespace into a single space.
std::string NodeText(const GumboNode * node);

/// Strip html tags of a `node`. If `smart_wrap` is enabled, the content of
/// some elements is embedded in newlines. For example,
/// `This is<div>a</div>sentence.` becomes `This is\na\nsentence.`. If
/// `smart_wrap` is disabled, the result will be `This isasentence.`.
/// See implementation of hext::TagWrapsText for a list of affected elements.
std::string StripTags(const GumboNode * node, bool smart_wrap = false);

/// Get inner html of a `node`, as is, untouched.
std::string NodeInnerHtml(const GumboNode * node);

/// Return true if `tag` is a tag for an element that is to be embedded
/// in newlines when converting html to text (that excludes most inline
/// elements, e.g. `<span>`).
bool TagWrapsText(GumboTag tag);


} // namespace hext


#endif // HEXT_NODE_UTIL_H_INCLUDED

