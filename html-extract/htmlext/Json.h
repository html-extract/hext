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


/// Print ResultTree as json.
/// If a name already exists it is converted to an array and the new value is
/// appended.
///
/// Example:
///   {"foo": "bar"} and {"foo", "baz"}
/// produces:
///   {"foo": ["bar", "baz"]}
void PrintJson(const hext::ResultTree * rt, std::ostream& out);

/// Append all values in `rt` to `obj`.
void AppendValuesJson(
  const hext::ResultTree * rt,
  rapidjson::Value& obj,
  rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& alloc
);


} // namespace htmlext


#endif // HTMLEXT_JSON_H_INCLUDED

