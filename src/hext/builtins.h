#ifndef HEXT_BUILTINS_H
#define HEXT_BUILTINS_H

#include <cassert>
#include <string>

#include <gumbo.h>


namespace hext {
namespace bi {


typedef std::string (*builtin_func_ptr)(const GumboNode *);

builtin_func_ptr get_builtin_by_name(const std::string& builtin_name);
std::string get_name_by_builtin(builtin_func_ptr f);
std::string text(const GumboNode * node);
std::string raw_text(const GumboNode * node);


} // namespace bi
} // namespace hext


#endif // HEXT_BUILTINS_H

