#include "hext/Builtins.h"

#include "NodeUtil.h"

#include <string>


namespace hext {


namespace {


/// A wrapper for hext::StripTags with disabled smart_wrap. Builtin functions
/// can only have a single parameter (node).
std::string StripTagsWrapper(const GumboNode * node)
{
  return StripTags(node, /* smart_wrap: */ false);
}


} // namespace


/// Instantiates a CaptureFunction that calls NodeText.
const CaptureFunction TextBuiltin = CaptureFunction(NodeText);


/// Instantiates a CaptureFunction that calls NodeInnerHtml.
const CaptureFunction InnerHtmlBuiltin = CaptureFunction(NodeInnerHtml);


/// Instantiates a CaptureFunction that calls StripTagsWrapper which is a
/// wrapper for StripTags.
const CaptureFunction StripTagsBuiltin = CaptureFunction(StripTagsWrapper);


} // namespace hext

