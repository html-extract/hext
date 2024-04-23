// Copyright 2024 Thomas Trapp
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

#include "hext/TypeRegexMatch.h"

#include <cassert>
#include <string_view>
#include <utility>


namespace hext {


TypeRegexMatch::TypeRegexMatch(boost::regex regex)
: rx_(std::move(regex))  // not noexcept
{
}

bool TypeRegexMatch::matches(const GumboNode * node) const
{
  assert(node);
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return boost::regex_search("", this->rx_);

  const GumboElement& e = (node->v).element;
  if( e.tag == GUMBO_TAG_UNKNOWN )
  {
    GumboStringPiece tagname = e.original_tag;
    gumbo_tag_from_original_text(&tagname);
    const auto sv = std::string_view(tagname.data, tagname.length);
    return boost::regex_search(sv.cbegin(), sv.cend(), this->rx_);
  }

  const char * subject = gumbo_normalized_tagname(e.tag);
  return boost::regex_search(subject, this->rx_);
}


} // namespace hext

