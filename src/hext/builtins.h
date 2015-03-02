#ifndef HEXT_BUILTINS_H_INCLUDED
#define HEXT_BUILTINS_H_INCLUDED

#include "hext/node-util.h"

#include <cassert>
#include <string>

#include <gumbo.h>


namespace hext {


/// Convenience typedef for function pointers pointing to so called builtin
/// functions (like @text)
typedef std::string (*BuiltinFuncPtr)(const GumboNode *);

/// Return a function pointer to a builtin called builtin_name.
BuiltinFuncPtr GetBuiltinByName(const std::string& builtin_name);
/// Return the name of the builtin which is pointed to by f.
std::string GetNameByBuiltin(BuiltinFuncPtr f);


} // namespace hext


#endif // HEXT_BUILTINS_H_INCLUDED

