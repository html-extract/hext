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

const CaptureFunction TextBuiltin = CaptureFunction(NodeText);
const CaptureFunction InnerHtmlBuiltin = CaptureFunction(NodeInnerHtml);
const CaptureFunction StripTagsBuiltin = CaptureFunction(StripTagsWrapper);


} // namespace hext

