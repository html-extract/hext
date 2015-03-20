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
	23, 1, 24, 1, 25, 1, 26, 1, 
	28, 1, 30, 1, 31, 2, 1, 32, 
	2, 11, 22, 2, 13, 22, 2, 16, 
	17, 2, 18, 19, 2, 24, 27, 2, 
	24, 29, 2, 25, 27, 2, 25, 29, 
	2, 26, 29, 2, 28, 29, 3, 0, 
	1, 32
};

static const unsigned char _hext_key_offsets[] = {
	0, 0, 2, 5, 6, 20, 28, 32, 
	46, 49, 53, 57, 62, 63, 65, 67, 
	68, 71, 74, 76, 78, 79, 80, 94, 
	104, 107, 108, 109, 110, 111, 116, 117, 
	118, 119, 120, 121, 122, 123, 124, 125, 
	126, 131, 132, 133, 134, 135, 136, 137, 
	138, 139, 140, 142, 146, 151, 153, 155, 
	158, 172, 184, 197, 200
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
	101, 102, 110, 109, 112, 116, 121, 10, 
	32, 62, 9, 13, 105, 114, 115, 116, 
	45, 99, 104, 105, 108, 100, 10, 32, 
	62, 9, 13, 116, 104, 45, 99, 104, 
	105, 108, 100, 40, 48, 57, 41, 110, 
	48, 57, 10, 32, 62, 9, 13, 41, 
	43, 48, 57, 41, 48, 57, 10, 32, 
	45, 58, 62, 95, 9, 13, 48, 57, 
	65, 90, 97, 122, 10, 32, 58, 62, 
	9, 13, 48, 57, 65, 90, 97, 122, 
	10, 32, 33, 58, 62, 9, 13, 49, 
	57, 65, 90, 97, 122, 32, 35, 60, 
	32, 35, 60, 0
};

static const char _hext_single_lengths[] = {
	0, 2, 3, 1, 6, 2, 0, 6, 
	3, 4, 4, 3, 1, 2, 2, 1, 
	3, 3, 2, 2, 1, 1, 6, 4, 
	3, 1, 1, 1, 1, 3, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	3, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 0, 2, 3, 2, 0, 1, 
	6, 4, 5, 3, 3
};

static const char _hext_range_lengths[] = {
	0, 0, 0, 0, 4, 3, 2, 4, 
	0, 0, 0, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 4, 3, 
	0, 0, 0, 0, 0, 1, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	1, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 1, 1, 0, 1, 1, 
	4, 4, 4, 0, 0
};

static const short _hext_index_offsets[] = {
	0, 0, 3, 7, 9, 20, 26, 29, 
	40, 44, 49, 54, 59, 61, 64, 67, 
	69, 73, 77, 80, 83, 85, 87, 98, 
	106, 110, 112, 114, 116, 118, 123, 125, 
	127, 129, 131, 133, 135, 137, 139, 141, 
	143, 148, 150, 152, 154, 156, 158, 160, 
	162, 164, 166, 168, 172, 177, 180, 182, 
	185, 196, 205, 215, 219
};

static const char _hext_trans_targs[] = {
	2, 3, 0, 1, 3, 4, 0, 60, 
	3, 60, 5, 23, 24, 12, 58, 5, 
	57, 56, 56, 0, 5, 6, 5, 22, 
	22, 0, 7, 7, 0, 60, 5, 7, 
	8, 12, 7, 5, 7, 7, 7, 0, 
	9, 13, 16, 0, 0, 0, 0, 0, 
	10, 11, 0, 0, 0, 10, 60, 5, 
	12, 5, 0, 60, 0, 11, 15, 14, 
	11, 15, 14, 15, 14, 0, 0, 0, 
	17, 18, 0, 11, 17, 20, 21, 19, 
	20, 21, 19, 11, 0, 21, 19, 60, 
	5, 22, 8, 12, 22, 5, 22, 22, 
	22, 0, 60, 5, 24, 12, 5, 56, 
	56, 0, 25, 30, 41, 0, 26, 0, 
	27, 0, 28, 0, 29, 0, 60, 5, 
	12, 5, 0, 31, 0, 32, 0, 33, 
	0, 34, 0, 35, 0, 36, 0, 37, 
	0, 38, 0, 39, 0, 40, 0, 60, 
	5, 12, 5, 0, 42, 0, 43, 0, 
	44, 0, 45, 0, 46, 0, 47, 0, 
	48, 0, 49, 0, 50, 0, 51, 0, 
	52, 53, 51, 0, 60, 5, 12, 5, 
	0, 52, 54, 0, 55, 0, 52, 55, 
	0, 60, 5, 56, 24, 12, 56, 5, 
	56, 56, 56, 0, 60, 5, 24, 12, 
	5, 57, 56, 56, 0, 60, 5, 23, 
	24, 12, 5, 57, 56, 56, 0, 1, 
	3, 4, 0, 1, 3, 4, 0, 0
};

static const char _hext_trans_actions[] = {
	0, 0, 1, 47, 0, 47, 1, 0, 
	0, 49, 49, 49, 49, 49, 49, 49, 
	76, 79, 79, 1, 0, 0, 0, 25, 
	25, 1, 21, 21, 1, 64, 64, 0, 
	23, 64, 0, 64, 0, 0, 0, 1, 
	0, 0, 0, 1, 1, 1, 1, 1, 
	41, 43, 1, 1, 1, 0, 45, 45, 
	45, 45, 1, 59, 1, 73, 37, 37, 
	39, 0, 0, 0, 0, 1, 1, 1, 
	29, 31, 1, 31, 0, 70, 33, 33, 
	35, 0, 0, 0, 1, 0, 0, 67, 
	67, 0, 27, 67, 0, 67, 0, 0, 
	0, 1, 53, 53, 53, 53, 53, 88, 
	88, 1, 0, 0, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 17, 17, 
	17, 17, 1, 0, 1, 0, 1, 0, 
	1, 0, 1, 0, 1, 0, 1, 0, 
	1, 0, 1, 0, 1, 0, 1, 19, 
	19, 19, 19, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 5, 1, 
	7, 7, 0, 1, 15, 15, 15, 15, 
	1, 9, 9, 1, 11, 1, 13, 0, 
	1, 57, 57, 0, 57, 57, 0, 57, 
	0, 0, 0, 1, 55, 55, 55, 55, 
	55, 0, 91, 91, 1, 51, 51, 51, 
	51, 51, 51, 82, 85, 85, 1, 0, 
	0, 0, 1, 3, 3, 3, 1, 0
};

static const char _hext_eof_actions[] = {
	0, 94, 94, 94, 94, 94, 94, 94, 
	94, 94, 94, 94, 94, 94, 94, 94, 
	94, 94, 94, 94, 94, 94, 94, 94, 
	94, 94, 94, 94, 94, 94, 94, 94, 
	94, 94, 94, 94, 94, 94, 94, 94, 
	94, 94, 94, 94, 94, 94, 94, 94, 
	94, 94, 94, 94, 94, 94, 94, 94, 
	94, 94, 94, 61, 61
};

static const int hext_start = 59;
static const int hext_first_final = 59;
static const int hext_error = 0;

static const int hext_en_main = 59;


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

