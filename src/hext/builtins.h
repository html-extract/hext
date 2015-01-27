#ifndef HEXT_BUILTIN_CAPTURES_H
#define HEXT_BUILTIN_CAPTURES_H

#include <cassert>
#include <string>

#include <gumbo.h>


namespace hext {
namespace bc {


std::string capture_inner_text(const GumboNode * node);


} // namespace bc
} // namespace hext


#endif // HEXT_BUILTIN_CAPTURES_H

