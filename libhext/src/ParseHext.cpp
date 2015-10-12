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

#include "hext/ParseHext.h"

#include "Parser.h"

#include <cstring>


namespace hext {


Rule ParseHext(const char * hext)
{
  return ParseHext(hext, std::strlen(hext));
}

Rule ParseHext(const char * hext, std::size_t size)
{
  Parser parser(hext, hext + size);
  return parser.parse();
}


} // namespace hext

