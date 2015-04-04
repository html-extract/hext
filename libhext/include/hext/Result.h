#ifndef HEXT_RESULT_H_INCLUDED
#define HEXT_RESULT_H_INCLUDED

#include <map>
#include <vector>
#include <string>


namespace hext {


/// A string-pair containg a name and a value.
typedef std::pair<std::string, std::string> ResultPair;

/// A multimap containing the values produced by capturing.
typedef std::multimap<std::string, std::string> ResultMap;

/// A collection of ResultMaps.
typedef std::vector<ResultMap> Result;


} // namespace hext


#endif // HEXT_RESULT_H_INCLUDED

