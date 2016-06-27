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

#ifndef HTMLEXT_VERSION_H_INCLUDED
#define HTMLEXT_VERSION_H_INCLUDED

#include "hext/Version.h"

#include <iostream>


namespace htmlext {


/// Major version numer.
extern const int version_major;

/// Minor version number.
extern const int version_minor;


/// Print version to out.
void PrintVersion(std::ostream& out = std::cout);


} // namespace htmlext


#endif // HTMLEXT_VERSION_H_INCLUDED

