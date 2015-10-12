// Copyright 2015 Thomas Trapp
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

