#ifndef HEXT_BUILTINS_H
#define HEXT_BUILTINS_H

#include <cassert>
#include <string>

#include <gumbo.h>


namespace hext {
namespace bi {


std::string capture_inner_text(const GumboNode * node);


} // namespace bi
} // namespace hext


#endif // HEXT_BUILTINS_H

