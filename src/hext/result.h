#ifndef HEXT_RESULT_H_INCLUDED
#define HEXT_RESULT_H_INCLUDED

#include <map>
#include <vector>
#include <string>


namespace hext {


/// A ResultMap contains the values produced by capturing.
typedef std::multimap<std::string, std::string> ResultMap;

/// Convenience typedef for a collection of Results.
typedef std::vector<ResultMap> Result;


} // namespace hext


#endif // HEXT_RESULT_H_INCLUDED

