#ifndef HEXT_BUILTINS_H_INCLUDED
#define HEXT_BUILTINS_H_INCLUDED

#include "hext/NodeUtil.h"

#include <cassert>
#include <string>

#include <gumbo.h>


namespace hext {


/// Convenience typedef for function pointers pointing to builtin
/// functions (like `@text`).
typedef std::string (*BuiltinFuncPtr)(const GumboNode *);

/// Return a function pointer to a builtin called `builtin_name`.
/// Return nullptr for unknown builtin.
BuiltinFuncPtr GetBuiltinByName(const std::string& builtin_name);

/// A wrapper for hext::StripTags with disabled smart_wrap. Builtin functions
/// can only have a single paramter (node).
std::string StripTagsWrapper(const GumboNode * node);


} // namespace hext


#endif // HEXT_BUILTINS_H_INCLUDED

