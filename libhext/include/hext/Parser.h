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
	23, 1, 24, 1, 25, 1, 27, 1, 
	29, 1, 30, 2, 1, 31, 2, 10, 
	21, 2, 12, 21, 2, 15, 16, 2, 
	17, 18, 2, 23, 26, 2, 23, 28, 
	2, 24, 26, 2, 24, 28, 2, 25, 
	28, 2, 27, 28, 3, 0, 1, 31
	
};

static const unsigned char _hext_key_offsets[] = {
	0, 0, 2, 5, 6, 20, 28, 32, 
	46, 49, 53, 57, 62, 63, 65, 67, 
	68, 71, 74, 76, 78, 79, 80, 94, 
	104, 106, 107, 108, 109, 110, 115, 116, 
	117, 118, 119, 120, 121, 122, 123, 124, 
	126, 130, 135, 137, 139, 142, 156, 168, 
	181, 184
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
	101, 110, 109, 112, 116, 121, 10, 32, 
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
	2, 1, 1, 1, 1, 3, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 0, 
	2, 3, 2, 0, 1, 6, 4, 5, 
	3, 3
};

static const char _hext_range_lengths[] = {
	0, 0, 0, 0, 4, 3, 2, 4, 
	0, 0, 0, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 4, 3, 
	0, 0, 0, 0, 0, 1, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 1, 
	1, 1, 0, 1, 1, 4, 4, 4, 
	0, 0
};

static const unsigned char _hext_index_offsets[] = {
	0, 0, 3, 7, 9, 20, 26, 29, 
	40, 44, 49, 54, 59, 61, 64, 67, 
	69, 73, 77, 80, 83, 85, 87, 98, 
	106, 109, 111, 113, 115, 117, 122, 124, 
	126, 128, 130, 132, 134, 136, 138, 140, 
	142, 146, 151, 154, 156, 159, 170, 179, 
	189, 193
};

static const char _hext_trans_targs[] = {
	2, 3, 0, 1, 3, 4, 0, 49, 
	3, 49, 5, 23, 24, 12, 47, 5, 
	46, 45, 45, 0, 5, 6, 5, 22, 
	22, 0, 7, 7, 0, 49, 5, 7, 
	8, 12, 7, 5, 7, 7, 7, 0, 
	9, 13, 16, 0, 0, 0, 0, 0, 
	10, 11, 0, 0, 0, 10, 49, 5, 
	12, 5, 0, 49, 0, 11, 15, 14, 
	11, 15, 14, 15, 14, 0, 0, 0, 
	17, 18, 0, 11, 17, 20, 21, 19, 
	20, 21, 19, 11, 0, 21, 19, 49, 
	5, 22, 8, 12, 22, 5, 22, 22, 
	22, 0, 49, 5, 24, 12, 5, 45, 
	45, 0, 25, 30, 0, 26, 0, 27, 
	0, 28, 0, 29, 0, 49, 5, 12, 
	5, 0, 31, 0, 32, 0, 33, 0, 
	34, 0, 35, 0, 36, 0, 37, 0, 
	38, 0, 39, 0, 40, 0, 41, 42, 
	40, 0, 49, 5, 12, 5, 0, 41, 
	43, 0, 44, 0, 41, 44, 0, 49, 
	5, 45, 24, 12, 45, 5, 45, 45, 
	45, 0, 49, 5, 24, 12, 5, 46, 
	45, 45, 0, 49, 5, 23, 24, 12, 
	5, 46, 45, 45, 0, 1, 3, 4, 
	0, 1, 3, 4, 0, 0
};

static const char _hext_trans_actions[] = {
	0, 0, 1, 45, 0, 45, 1, 0, 
	0, 47, 47, 47, 47, 47, 47, 47, 
	74, 77, 77, 1, 0, 0, 0, 23, 
	23, 1, 19, 19, 1, 62, 62, 0, 
	21, 62, 0, 62, 0, 0, 0, 1, 
	0, 0, 0, 1, 1, 1, 1, 1, 
	39, 41, 1, 1, 1, 0, 43, 43, 
	43, 43, 1, 57, 1, 71, 35, 35, 
	37, 0, 0, 0, 0, 1, 1, 1, 
	27, 29, 1, 29, 0, 68, 31, 31, 
	33, 0, 0, 0, 1, 0, 0, 65, 
	65, 0, 25, 65, 0, 65, 0, 0, 
	0, 1, 51, 51, 51, 51, 51, 86, 
	86, 1, 0, 0, 1, 0, 1, 0, 
	1, 0, 1, 0, 1, 17, 17, 17, 
	17, 1, 0, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 5, 1, 7, 7, 
	0, 1, 15, 15, 15, 15, 1, 9, 
	9, 1, 11, 1, 13, 0, 1, 55, 
	55, 0, 55, 55, 0, 55, 0, 0, 
	0, 1, 53, 53, 53, 53, 53, 0, 
	89, 89, 1, 49, 49, 49, 49, 49, 
	49, 80, 83, 83, 1, 0, 0, 0, 
	1, 3, 3, 3, 1, 0
};

static const char _hext_eof_actions[] = {
	0, 92, 92, 92, 92, 92, 92, 92, 
	92, 92, 92, 92, 92, 92, 92, 92, 
	92, 92, 92, 92, 92, 92, 92, 92, 
	92, 92, 92, 92, 92, 92, 92, 92, 
	92, 92, 92, 92, 92, 92, 92, 92, 
	92, 92, 92, 92, 92, 92, 92, 92, 
	59, 59
};

static const int hext_start = 48;
static const int hext_first_final = 48;
static const int hext_error = 0;

static const int hext_en_main = 48;


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

