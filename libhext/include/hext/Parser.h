// This file was generated from Parser.h.rl.

#line 1 "Parser.h.rl"
#ifndef HEXT_PARSER_H_INCLUDED
#define HEXT_PARSER_H_INCLUDED

#include "hext/StringUtil.h"
#include "hext/Builtins.h"
#include "hext/Rule.h"
#include "hext/RuleBuilder.h"

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <algorithm>

#include <boost/regex/regex_traits.hpp>
#include <boost/regex/pattern_except.hpp>


/// Convenience macro to store the start of a token. Used within the hext
/// machine definition. Accesses Parser::parse()'s local variables.
#define LX_TK_START \
  tok_begin = p;    \
  tok_end = nullptr;


/// Convenience macro to complete a token. Used within the hext
/// machine defintion. Accesses Parser::parse()'s local variables.
#define LX_TK_STOP              \
  assert(tok_begin != nullptr); \
  tok_end = p;                  \
  tok = std::string(tok_begin, std::distance(tok_begin, tok_end));


namespace hext {


/// ParseError is a custom exception class thrown for all errors that occur
/// while parsing hext.
/// Note: Clang warns (-Wweak-vtables) that a vtable for ParseError may be
/// placed in every translation unit, because ParseError doesn't have any
/// 'out-of-line virtual method definitions', where it would normally put
/// the vtable. But http://stackoverflow.com/a/23749273 suggests that this
/// is a non-issue; the linker will clean it up.
class ParseError : public std::runtime_error
{
public:
  explicit ParseError(const std::string& msg);
};


/// The ragel namespace holds ragel's static data.
namespace ragel {
  
#line 58 "Parser.h.tmp"
static const char _hext_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 1, 9, 1, 10, 1, 
	11, 1, 12, 1, 13, 1, 14, 1, 
	15, 1, 16, 1, 17, 1, 18, 1, 
	19, 1, 20, 1, 21, 1, 22, 1, 
	23, 1, 24, 1, 26, 1, 28, 1, 
	29, 2, 1, 30, 2, 9, 20, 2, 
	11, 20, 2, 14, 15, 2, 16, 17, 
	2, 22, 25, 2, 22, 27, 2, 23, 
	25, 2, 23, 27, 2, 24, 27, 2, 
	26, 27, 3, 0, 1, 30
};

static const unsigned char _hext_key_offsets[] = {
	0, 0, 2, 5, 6, 20, 28, 32, 
	46, 49, 53, 57, 62, 63, 65, 67, 
	68, 71, 74, 76, 78, 79, 80, 94, 
	104, 105, 106, 107, 108, 109, 110, 111, 
	112, 113, 114, 116, 120, 125, 127, 129, 
	132, 146, 158, 171, 174
};

static const char _hext_trans_keys[] = {
	32, 35, 32, 35, 60, 10, 10, 32, 
	33, 58, 62, 63, 9, 13, 49, 57, 
	65, 90, 97, 122, 32, 64, 9, 13, 
	65, 90, 97, 122, 65, 90, 97, 122, 
	10, 32, 45, 61, 62, 95, 9, 13, 
	48, 57, 65, 90, 97, 122, 34, 47, 
	123, 34, 47, 123, 125, 34, 47, 123, 
	125, 10, 32, 62, 9, 13, 10, 47, 
	92, 47, 92, 92, 47, 123, 125, 47, 
	123, 125, 47, 92, 47, 92, 125, 92, 
	10, 32, 45, 61, 62, 95, 9, 13, 
	48, 57, 65, 90, 97, 122, 10, 32, 
	58, 62, 9, 13, 65, 90, 97, 122, 
	110, 116, 104, 45, 99, 104, 105, 108, 
	100, 40, 48, 57, 41, 110, 48, 57, 
	10, 32, 62, 9, 13, 41, 43, 48, 
	57, 41, 48, 57, 10, 32, 45, 58, 
	62, 95, 9, 13, 48, 57, 65, 90, 
	97, 122, 10, 32, 58, 62, 9, 13, 
	48, 57, 65, 90, 97, 122, 10, 32, 
	33, 58, 62, 9, 13, 49, 57, 65, 
	90, 97, 122, 32, 35, 60, 32, 35, 
	60, 0
};

static const char _hext_single_lengths[] = {
	0, 2, 3, 1, 6, 2, 0, 6, 
	3, 4, 4, 3, 1, 2, 2, 1, 
	3, 3, 2, 2, 1, 1, 6, 4, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 0, 2, 3, 2, 0, 1, 
	6, 4, 5, 3, 3
};

static const char _hext_range_lengths[] = {
	0, 0, 0, 0, 4, 3, 2, 4, 
	0, 0, 0, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 4, 3, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 1, 1, 0, 1, 1, 
	4, 4, 4, 0, 0
};

static const unsigned char _hext_index_offsets[] = {
	0, 0, 3, 7, 9, 20, 26, 29, 
	40, 44, 49, 54, 59, 61, 64, 67, 
	69, 73, 77, 80, 83, 85, 87, 98, 
	106, 108, 110, 112, 114, 116, 118, 120, 
	122, 124, 126, 128, 132, 137, 140, 142, 
	145, 156, 165, 175, 179
};

static const char _hext_trans_targs[] = {
	2, 3, 0, 1, 3, 4, 0, 44, 
	3, 44, 5, 23, 24, 12, 42, 5, 
	41, 40, 40, 0, 5, 6, 5, 22, 
	22, 0, 7, 7, 0, 44, 5, 7, 
	8, 12, 7, 5, 7, 7, 7, 0, 
	9, 13, 16, 0, 0, 0, 0, 0, 
	10, 11, 0, 0, 0, 10, 44, 5, 
	12, 5, 0, 44, 0, 11, 15, 14, 
	11, 15, 14, 15, 14, 0, 0, 0, 
	17, 18, 0, 11, 17, 20, 21, 19, 
	20, 21, 19, 11, 0, 21, 19, 44, 
	5, 22, 8, 12, 22, 5, 22, 22, 
	22, 0, 44, 5, 24, 12, 5, 40, 
	40, 0, 25, 0, 26, 0, 27, 0, 
	28, 0, 29, 0, 30, 0, 31, 0, 
	32, 0, 33, 0, 34, 0, 35, 0, 
	36, 37, 35, 0, 44, 5, 12, 5, 
	0, 36, 38, 0, 39, 0, 36, 39, 
	0, 44, 5, 40, 24, 12, 40, 5, 
	40, 40, 40, 0, 44, 5, 24, 12, 
	5, 41, 40, 40, 0, 44, 5, 23, 
	24, 12, 5, 41, 40, 40, 0, 1, 
	3, 4, 0, 1, 3, 4, 0, 0
};

static const char _hext_trans_actions[] = {
	0, 0, 1, 43, 0, 43, 1, 0, 
	0, 45, 45, 45, 45, 45, 45, 45, 
	72, 75, 75, 1, 0, 0, 0, 21, 
	21, 1, 17, 17, 1, 60, 60, 0, 
	19, 60, 0, 60, 0, 0, 0, 1, 
	0, 0, 0, 1, 1, 1, 1, 1, 
	37, 39, 1, 1, 1, 0, 41, 41, 
	41, 41, 1, 55, 1, 69, 33, 33, 
	35, 0, 0, 0, 0, 1, 1, 1, 
	25, 27, 1, 27, 0, 66, 29, 29, 
	31, 0, 0, 0, 1, 0, 0, 63, 
	63, 0, 23, 63, 0, 63, 0, 0, 
	0, 1, 49, 49, 49, 49, 49, 84, 
	84, 1, 0, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 5, 1, 
	7, 7, 0, 1, 15, 15, 15, 15, 
	1, 9, 9, 1, 11, 1, 13, 0, 
	1, 53, 53, 0, 53, 53, 0, 53, 
	0, 0, 0, 1, 51, 51, 51, 51, 
	51, 0, 87, 87, 1, 47, 47, 47, 
	47, 47, 47, 78, 81, 81, 1, 0, 
	0, 0, 1, 3, 3, 3, 1, 0
};

static const char _hext_eof_actions[] = {
	0, 90, 90, 90, 90, 90, 90, 90, 
	90, 90, 90, 90, 90, 90, 90, 90, 
	90, 90, 90, 90, 90, 90, 90, 90, 
	90, 90, 90, 90, 90, 90, 90, 90, 
	90, 90, 90, 90, 90, 90, 90, 90, 
	90, 90, 90, 57, 57
};

static const int hext_start = 43;
static const int hext_first_final = 43;
static const int hext_error = 0;

static const int hext_en_main = 43;


#line 58 "Parser.h.rl"

} // namespace ragel


/// Parser is responsible for parsing hext and producing Rules.
class Parser
{
public:
  /// Construct a Parser to parse hext rule definitions described in range begin
  /// to end. Pointers must stay valid until the last call to Parser::parse().
  Parser(const char * begin, const char * end);

  /// Parse hext and produce a vector of rules.
  /// Throws ParseError on invalid input.
  std::vector<Rule> parse();

private:
  /// Throw ParseError with an error message marking an unexpected character.
  void throw_unexpected() const;

  /// Throw ParseError with an error message marking an unknown token.
  void throw_unknown_token(
    const std::string& tok,
    const std::string& tok_name
  ) const;

  /// Throw ParseError with an error message marking an invalid regular
  /// expression.
  void throw_regex_error(
    const std::string& tok,
    boost::regex_constants::error_type e_code
  ) const;

  /// Print an error at the current location within hext. Print hext with line
  /// numbers up to the currently examined character. mark_len denotes the
  /// amount of '^' characters that are used to mark the error location up to
  /// the current character.
  void print_error_location(
    std::string::size_type mark_len,
    std::ostream& out
  ) const;

  /// A pointer to the beginning of the overall input is needed to provide
  /// good error diagnostics.
  const char * p_begin_;

  /// ragel's runtime state
  const char * p;
  const char * pe;
  const char * eof;
  int cs;
};


} // namespace hext


#endif // HEXT_PARSER_H_INCLUDED

