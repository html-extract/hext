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

#ifndef HEXT_RESULT_H_INCLUDED
#define HEXT_RESULT_H_INCLUDED

/// @file
///   Typedefs for results returned from capturing HTML.

#include <map>
#include <vector>
#include <string>
#include <utility>


namespace hext {


/// A string-pair containing a name and a value. A ResultPair is produced by a
/// Capture.
using ResultPair = std::pair<std::string, std::string>;


/// A multimap containing the values produced by capturing.
/// Why std::multimap?
/// * The value of a Capture should be accessible by key => associative
/// * There may be Captures with duplicate names         => multi key
/// * The order of Captures should be predictable        => sorted
using ResultMap = std::multimap<ResultPair::first_type,
                                ResultPair::second_type>;


/// A vector containing ResultMap.
using Result = std::vector<ResultMap>;


} // namespace hext


#endif // HEXT_RESULT_H_INCLUDED

