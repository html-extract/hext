#ifndef HEXT_CAPTURE_FUNCTION_H_INCLUDED
#define HEXT_CAPTURE_FUNCTION_H_INCLUDED

/// @file
///   Declares hext::CaptureFunction

#include <functional>
#include <string>

#include <gumbo.h>


namespace hext {


/// A type of std::function that receives an HTML element and returns a string.
typedef std::function<std::string (const GumboNode *)> CaptureFunction;


} // namespace hext


#endif // HEXT_CAPTURE_FUNCTION_H_INCLUDED

