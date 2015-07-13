#ifndef HEXT_CAPTURE_FUNCTION_H_INCLUDED
#define HEXT_CAPTURE_FUNCTION_H_INCLUDED

#include <functional>
#include <string>

#include <gumbo.h>


namespace hext {


typedef
  std::function<std::string (const GumboNode *)>
    CaptureFunction;


} // namespace hext


#endif // HEXT_CAPTURE_FUNCTION_H_INCLUDED

