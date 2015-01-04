#ifndef HEXT_UTIL_H
#define HEXT_UTIL_H

#include <string>


namespace hext {
namespace util {


/// Prepend a slash to all double-quotes (")
std::string escape_quotes(const std::string& str);


} // namespace util
} // namespace hext


#endif // HEXT_UTIL_H

