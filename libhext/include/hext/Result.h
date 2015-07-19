#ifndef HEXT_RESULT_H_INCLUDED
#define HEXT_RESULT_H_INCLUDED

/// @file
///   Typedefs for results returned from capturing HTML.

#include <unordered_map>
#include <vector>
#include <string>
#include <utility>


namespace hext {


/// A string-pair containing a name and a value. A ResultPair is produced by a
/// Capture.
typedef std::pair<std::string, std::string> ResultPair;


/// A multimap containing the values produced by capturing. A ResultTree can be
/// flattened to a vector containing ResultMap.
typedef std::unordered_multimap<
  ResultPair::first_type,
  ResultPair::second_type
> ResultMap;


/// A vector containing ResultMap. A ResultTree can be flattened to a Result.
typedef std::vector<ResultMap> Result;


} // namespace hext


#endif // HEXT_RESULT_H_INCLUDED

