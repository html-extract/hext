#ifndef HEXT_PARSER_H_INCLUDED
#define HEXT_PARSER_H_INCLUDED

/// @file
///   Declares hext::Parser

#include "hext/Rule.h"
#include "hext/SyntaxError.h"

#include <memory>


namespace hext {


/// Parses a string containing hext rule definitions.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   std::string hext_str("<a href={href}/>");
///   Parser p(hext_str.begin(), hext_str.end());
///   try {
///     Rule rule = p.parse();
///     // ... do sth. with rule ...
///   } catch( SyntaxError& e ) {
///     // e.what() will contain a detailed error message.
///   }
/// ~~~~~~~~~~~~~
class Parser
{
public:
  /// Constructs a Parser to parse hext rule definitions contained in
  /// range [begin, end). Pointers are non-owning and must stay valid until the
  /// last call to Parser::parse().
  Parser(const char * begin, const char * end);

  ~Parser() noexcept;
  Parser(Parser&&) noexcept;
  Parser& operator=(Parser&&) noexcept;

  /// Parses hext rule definition from the given range and returns the top level
  /// Rule. Throws SyntaxError with a detailed error message on invalid input.
  ///
  /// @throws SyntaxError
  Rule parse();

private:
  Parser(const Parser&) = delete;
  Parser& operator=(const Parser&) = delete;

  struct Impl;
  std::unique_ptr<Impl> impl_;
};


} // namespace hext


#endif // HEXT_PARSER_H_INCLUDED

