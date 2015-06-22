#ifndef HTMLEXT_JSON_H_INCLUDED
#define HTMLEXT_JSON_H_INCLUDED

#include "hext/ResultTree.h"

#include <map>
#include <iostream>

#include <rapidjson/allocators.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>


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
inline JsonOption operator|(JsonOption l, JsonOption r)
{
  return static_cast<JsonOption>(static_cast<int>(l) | static_cast<int>(r));
}

/// Convenience JsonOption AND-operator that does all the casting.
inline JsonOption operator&(JsonOption l, JsonOption r)
{
  return static_cast<JsonOption>(static_cast<int>(l) & static_cast<int>(r));
}

/// Print ResultTree as json.
/// If a name already exists it is converted to an array and the new value is
/// appended.
///
/// Example:
///   {"foo": "bar"} and {"foo", "baz"}
/// produces:
///   {"foo": ["bar", "baz"]}
void PrintJson(const hext::ResultTree * rt, JsonOption opt, std::ostream& out);

/// Print a rapidjson::Value to `out`.
void PrintJsonValue(
  const rapidjson::Value& value,
  JsonOption opt,
  std::ostream& out
);

/// Append all values in `rt` to `obj`.
void AppendValuesJson(
  const hext::ResultTree * rt,
  rapidjson::Value& obj,
  rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& alloc
);


} // namespace htmlext


#endif // HTMLEXT_JSON_H_INCLUDED

