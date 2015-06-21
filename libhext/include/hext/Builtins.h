#ifndef HEXT_BUILTINS_H_INCLUDED
#define HEXT_BUILTINS_H_INCLUDED

#include "hext/NodeUtil.h"

#include <string>

#include <gumbo.h>


namespace hext {


/// Convenience typedef for function pointers pointing to builtin
/// functions (like `@text`).
typedef std::string (*BuiltinFuncPtr)(const GumboNode *);

/// A wrapper for hext::StripTags with disabled smart_wrap. Builtin functions
/// can only have a single parameter (node).
inline std::string StripTagsWrapper(const GumboNode * node)
  { return StripTags(node, /* smart_wrap: */ false); }


} // namespace hext


#endif // HEXT_BUILTINS_H_INCLUDED

