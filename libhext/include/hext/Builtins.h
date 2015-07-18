#ifndef HEXT_BUILTINS_H_INCLUDED
#define HEXT_BUILTINS_H_INCLUDED

/// @file
///   Contains every predefined CaptureFunction.

#include "hext/CaptureFunction.h"


namespace hext {


/// A CaptureFunction that returns the text of an HTML element.
/// The intent is to mimic functions like jQuery's text(), IE's innerText() or
/// textContent().
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   GumboNode * node = ...; // <div> like<div>a</div>rolling  stone</div>
///   assert(TextBuiltin(node) == "like a rolling stone");
/// ~~~~~~~~~~~~~
///
/// @param node:  A pointer to a GumboNode.
/// @returns  A string containing the HTML element's text.
extern const CaptureFunction TextBuiltin;


/// A CaptureFunction that returns the inner HTML of an HTML element.
/// The intent is to mimic innerHtml().
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   GumboNode * node = ...; // <div> like<div>a</div>rolling  stone</div>
///   assert(InnerHtmlBuiltin(node) == " like<div>a</div>rolling  stone");
/// ~~~~~~~~~~~~~
///
/// @param node:  A pointer to a GumboNode.
/// @returns  A string containing the HTML element's inner HTML.
extern const CaptureFunction InnerHtmlBuiltin;


/// A CaptureFunction that returns the inner HTML of an HTML element without
/// tags.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   GumboNode * node = ...; // <div> like<div>a</div>rolling  stone</div>
///   assert(StripTagsBuiltin(node) == " likearolling  stone");
/// ~~~~~~~~~~~~~
///
/// @param node:  A pointer to a GumboNode.
/// @returns  A string containing the HTML element's inner HTML without tags.
extern const CaptureFunction StripTagsBuiltin;


} // namespace hext


#endif // HEXT_BUILTINS_H_INCLUDED

