#ifndef HEXT_STRING_UTIL_H
#define HEXT_STRING_UTIL_H

#include <cassert>
#include <cctype>
#include <string>
#include <utility>
#include <algorithm>
#include <iterator>


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

// Convenience typedefs for get_char_position.
typedef std::iterator_traits<const char *>::difference_type char_pos_type;
typedef std::pair<char_pos_type, char_pos_type> char_pos_pair;

/// Returns a visual representation for every char, including control
/// characters like the nullbyte.
/// Used in error reporting.
std::string get_char_name(char c);

/// Returns a pair<line_number, character_number> for the position of c in
/// the range from begin to end. Numbering is one-based.
/// Used in error reporting.
char_pos_pair get_char_position(
  const char * c,
  const char * begin,
  const char * end
);


} // namespace hext


#endif // HEXT_STRING_UTIL_H

