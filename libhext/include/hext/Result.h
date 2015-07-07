#ifndef HEXT_RESULT_H_INCLUDED
#define HEXT_RESULT_H_INCLUDED

#include <unordered_map>
#include <vector>
#include <string>
#include <utility>


namespace hext {


/// A string-pair containg a name and a value.
typedef std::pair<std::string, std::string> ResultPair;

/// A multimap containing the values produced by capturing.
typedef std::unordered_multimap<
  ResultPair::first_type,
  ResultPair::second_type
> ResultMap;

/// A collection of ResultMaps.
typedef std::vector<ResultMap> Result;


} // namespace hext


#endif // HEXT_RESULT_H_INCLUDED

