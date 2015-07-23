#ifndef HEXT_MATCH_FUNCTION_H_INCLUDED
#define HEXT_MATCH_FUNCTION_H_INCLUDED

/// @file
///   Declares hext::MatchFunction

#include <functional>

#include <gumbo.h>


namespace hext {


/// A type of std::function that receives an HTML element and returns a bool.
typedef std::function<bool (const GumboNode *)> MatchFunction;


} // namespace hext


#endif // HEXT_MATCH_FUNCTION_H_INCLUDED

