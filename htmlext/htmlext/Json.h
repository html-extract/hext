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

#ifndef HTMLEXT_JSON_H_INCLUDED
#define HTMLEXT_JSON_H_INCLUDED

#include "hext/Result.h"

#include <iostream>

#include <rapidjson/document.h>


namespace htmlext {


/// Options for JSON output.
enum class JsonOption
{
  NoOption      = 0,

  /// Prettify JSON output.
  PrettyPrint   = 1,

  /// Wrap JSON objects in a top-level JSON array.
  ArrayEnvelope = 2
};


/// Convenience JsonOption OR-operator that does all the casting.
inline JsonOption operator|(JsonOption l, JsonOption r) noexcept
{
  return static_cast<JsonOption>(static_cast<int>(l) | static_cast<int>(r));
}


/// Convenience JsonOption AND-operator that does all the casting.
inline JsonOption operator&(JsonOption l, JsonOption r) noexcept
{
  return static_cast<JsonOption>(static_cast<int>(l) & static_cast<int>(r));
}


/// Print Result as json.
/// If a name already exists it is converted to an array and the new value is
/// appended.
///
/// Example:
///   {"foo": "bar"} and {"foo", "baz"}
/// produces:
///   {"foo": ["bar", "baz"]}
void PrintJson(const hext::Result result, JsonOption opt, std::ostream& out);


/// Print a rapidjson::Value to `out`.
void PrintJsonValue(const rapidjson::Value& value,
                    JsonOption              opt,
                    std::ostream&           out);


} // namespace htmlext


#endif // HTMLEXT_JSON_H_INCLUDED

