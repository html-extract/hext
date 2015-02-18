#ifndef HEXT_BUILTINS_H
#define HEXT_BUILTINS_H

#include <cassert>
#include <string>
#include <cctype>

#include <gumbo.h>


namespace hext {
namespace bi {


typedef std::string (*builtin_func_ptr)(const GumboNode *);

builtin_func_ptr get_builtin_by_name(const std::string& builtin_name);
std::string get_name_by_builtin(builtin_func_ptr f);
std::string text(const GumboNode * node);
std::string raw_text(const GumboNode * node);
/// Remove whitespace from beginning and end and collapse multiple whitespace
/// to a single ' ', as is expected when extracting text from html.
/// Example: "   Like\na Rolling\n\tStone  " -> "Like a Rolling Stone"
/// http://www.w3.org/TR/html5/infrastructure.html#strip-and-collapse-whitespace
std::string trim_and_collapse_ws(std::string str);
std::string inner_html(const GumboNode * node);
/// Check if given character is a space character according to the html standard.
/// std::isspace is not suitable, because it is locale aware.
/// http://www.w3.org/TR/html5/infrastructure.html#space-character
bool is_space(char c);


} // namespace bi
} // namespace hext


#endif // HEXT_BUILTINS_H

