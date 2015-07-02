#ifndef HEXT_PARSER_H_INCLUDED
#define HEXT_PARSER_H_INCLUDED

#include "hext/Rule.h"
#include "hext/SyntaxError.h"

#include <memory>


namespace hext {


/// Parser is responsible for parsing hext and producing Rules.
class Parser
{
public:
  /// Construct a Parser to parse hext rule definitions described in range
  /// `begin` to `end`. Pointers must stay valid until the last call to
  /// `Parser::parse()`.
  Parser(const char * begin, const char * end);

  Parser(Parser&&);
  Parser& operator=(Parser&&);
  ~Parser();

  /// Parse hext and return the top level Rule. Throw `SyntaxError` on invalid
  /// input.
  Rule parse();

private:
  Parser(const Parser&) = delete;
  Parser& operator=(const Parser&) = delete;

  struct Impl;
  std::unique_ptr<Impl> impl_;
};


} // namespace hext


#endif // HEXT_PARSER_H_INCLUDED

