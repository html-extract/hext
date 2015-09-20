#ifndef HEXT_PARSE_HEXT_H_INCLUDED
#define HEXT_PARSE_HEXT_H_INCLUDED

/// @file
///   Declares hext::ParseHext

#include <cstddef>

#include "hext/Rule.h"
#include "hext/SyntaxError.h"


namespace hext {


/// Parses a null-terminated string containing hext rule definitions.
/// Throws SyntaxError with a detailed error message on invalid input.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   try {
///     Rule rule = ParseHext("<a href=>href/>");
///   } catch( SyntaxError& e ) {
///     // e.what() will contain a detailed error message.
///   }
/// ~~~~~~~~~~~~~
///
/// @throws SyntaxError
///
/// @param hext:  A null-terminated string containing hext rule definitions.
/// @returns      The parsed Rule.
Rule ParseHext(const char * hext);

/// Parses a buffer containing hext rule definitions.
/// Throws SyntaxError with a detailed error message on invalid input.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   std::string hext_str("<a href=>href/>");
///   try {
///     Rule rule = ParseHext(hext_str.c_str(), hext_str.size());
///     // ... do sth. with rule ...
///   } catch( SyntaxError& e ) {
///     // e.what() will contain a detailed error message.
///   }
/// ~~~~~~~~~~~~~
///
/// @throws SyntaxError
///
/// @param hext:  A string containing hext rule definitions.
/// @param size:  The length of the string.
/// @returns      The parsed Rule.
Rule ParseHext(const char * hext, std::size_t size);


} // namespace hext


#endif // HEXT_PARSE_HEXT_H_INCLUDED

