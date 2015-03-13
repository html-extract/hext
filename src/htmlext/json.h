#ifndef HTMLEXT_JSON_H_INCLUDED
#define HTMLEXT_JSON_H_INCLUDED

#include <map>
#include <iostream>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


namespace htmlext {


/// Print a multimap as json.
/// If a name already exists it is converted to an array and the new value is
/// appended.
///
/// Example:
///   {"foo": "bar"} and {"foo", "baz"}
/// produces:
///   {"foo": ["bar", "baz"]}
void PrintJson(
  const std::multimap<std::string, std::string>& values,
  std::ostream& out = std::cout
);


} // namespace htmlext


#endif // HTMLEXT_JSON_H_INCLUDED

