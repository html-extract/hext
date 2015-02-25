#ifndef HEXT_BUILTINS_H
#define HEXT_BUILTINS_H

#include <cassert>
#include <string>

#include <gumbo.h>

#include "hext/node-util.h"


namespace hext {


typedef std::string (*BuiltinFuncPtr)(const GumboNode *);

BuiltinFuncPtr GetBuiltinByName(const std::string& builtin_name);
std::string GetNameByBuiltin(BuiltinFuncPtr f);


} // namespace hext


#endif // HEXT_BUILTINS_H

