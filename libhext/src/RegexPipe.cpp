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

#include "hext/RegexPipe.h"


namespace hext {


RegexPipe::RegexPipe(boost::regex regex)
: regex_(std::move(regex))
{
}

std::string RegexPipe::transform(std::string str) const
{
  boost::match_results<const char *> mr;
  if( boost::regex_search(str.c_str(), mr, this->regex_) )
  {
    // If there are no parentheses contained within the regex, return whole
    // regex capture (mr[0]), if there are, then return the first one.
    return ( mr.size() > 1 ? mr[1] : mr[0] );
  }

  return "";
}


} // namespace hext

