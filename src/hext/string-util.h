#ifndef HEXT_STRING_UTIL_H
#define HEXT_STRING_UTIL_H

#include <string>


namespace hext {


/// Remove whitespace from beginning and end and collapse multiple whitespace
/// to a single ' ', as is expected when extracting text from html.
/// Example: "   Like\na Rolling\n\tStone  " -> "Like a Rolling Stone"
/// http://www.w3.org/TR/html5/infrastructure.html#strip-and-collapse-whitespace
std::string trim_and_collapse_ws(std::string str);
/// Check if given character is a space character according to the html spec.
/// std::isspace is not suitable, because it is locale aware.
/// http://www.w3.org/TR/html5/infrastructure.html#space-character
bool is_space(char c);


} // namespace hext


#endif // HEXT_STRING_UTIL_H

