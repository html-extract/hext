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

#include "hext/CasePipe.h"

#include <boost/algorithm/string.hpp>


namespace hext {


CasePipe::CasePipe(CasePipe::Option option) noexcept
: option_(option)
{
}

std::string CasePipe::transform(std::string str) const
{
  if( this->option_ & Option::ToLower )
    boost::algorithm::to_lower(str);
  else
    boost::algorithm::to_upper(str);

  return str;
}


} // namespace hext

