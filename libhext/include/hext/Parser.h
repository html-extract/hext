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
	27, 1, 28, 1, 29, 1, 30, 1, 
	31, 1, 32, 1, 34, 1, 36, 1, 
	37, 2, 1, 38, 2, 17, 28, 2, 
	19, 28, 2, 22, 23, 2, 24, 25, 
	2, 30, 33, 2, 30, 35, 2, 31, 
	33, 2, 31, 35, 2, 32, 35, 2, 
	34, 35, 3, 0, 1, 38
};

static const short _hext_key_offsets[] = {
	0, 0, 2, 5, 6, 20, 28, 32, 
	46, 49, 53, 57, 62, 63, 65, 67, 
	68, 71, 74, 76, 78, 79, 80, 94, 
	104, 108, 109, 110, 111, 112, 117, 118, 
	119, 120, 121, 122, 124, 125, 126, 127, 
	128, 133, 134, 135, 136, 137, 138, 139, 
	144, 145, 146, 147, 148, 150, 151, 152, 
	153, 154, 159, 160, 161, 162, 163, 164, 
	165, 170, 171, 172, 173, 176, 177, 178, 
	179, 180, 181, 183, 187, 192, 194, 196, 
	199, 200, 201, 202, 203, 205, 206, 207, 
	208, 209, 210, 212, 216, 221, 223, 225, 
	228, 229, 230, 231, 232, 233, 234, 235, 
	237, 241, 246, 248, 250, 253, 254, 255, 
	256, 257, 258, 259, 260, 262, 266, 271, 
	273, 275, 278, 292, 304, 317, 320
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
	101, 102, 108, 110, 109, 112, 116, 121, 
	10, 32, 62, 9, 13, 105, 114, 115, 
	116, 45, 99, 111, 104, 105, 108, 100, 
	10, 32, 62, 9, 13, 102, 45, 116, 
	121, 112, 101, 10, 32, 62, 9, 13, 
	97, 115, 116, 45, 99, 111, 104, 105, 
	108, 100, 10, 32, 62, 9, 13, 102, 
	45, 116, 121, 112, 101, 10, 32, 62, 
	9, 13, 116, 104, 45, 99, 108, 111, 
	104, 105, 108, 100, 40, 48, 57, 41, 
	110, 48, 57, 10, 32, 62, 9, 13, 
	41, 43, 48, 57, 41, 48, 57, 97, 
	115, 116, 45, 99, 111, 104, 105, 108, 
	100, 40, 48, 57, 41, 110, 48, 57, 
	10, 32, 62, 9, 13, 41, 43, 48, 
	57, 41, 48, 57, 102, 45, 116, 121, 
	112, 101, 40, 48, 57, 41, 110, 48, 
	57, 10, 32, 62, 9, 13, 41, 43, 
	48, 57, 41, 48, 57, 102, 45, 116, 
	121, 112, 101, 40, 48, 57, 41, 110, 
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
	4, 1, 1, 1, 1, 3, 1, 1, 
	1, 1, 1, 2, 1, 1, 1, 1, 
	3, 1, 1, 1, 1, 1, 1, 3, 
	1, 1, 1, 1, 2, 1, 1, 1, 
	1, 3, 1, 1, 1, 1, 1, 1, 
	3, 1, 1, 1, 3, 1, 1, 1, 
	1, 1, 0, 2, 3, 2, 0, 1, 
	1, 1, 1, 1, 2, 1, 1, 1, 
	1, 1, 0, 2, 3, 2, 0, 1, 
	1, 1, 1, 1, 1, 1, 1, 0, 
	2, 3, 2, 0, 1, 1, 1, 1, 
	1, 1, 1, 1, 0, 2, 3, 2, 
	0, 1, 6, 4, 5, 3, 3
};

static const char _hext_range_lengths[] = {
	0, 0, 0, 0, 4, 3, 2, 4, 
	0, 0, 0, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 4, 3, 
	0, 0, 0, 0, 0, 1, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	1, 0, 0, 0, 0, 0, 0, 1, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 1, 0, 0, 0, 0, 0, 0, 
	1, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 1, 1, 0, 1, 1, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 1, 1, 0, 1, 1, 
	0, 0, 0, 0, 0, 0, 0, 1, 
	1, 1, 0, 1, 1, 0, 0, 0, 
	0, 0, 0, 0, 1, 1, 1, 0, 
	1, 1, 4, 4, 4, 0, 0
};

static const short _hext_index_offsets[] = {
	0, 0, 3, 7, 9, 20, 26, 29, 
	40, 44, 49, 54, 59, 61, 64, 67, 
	69, 73, 77, 80, 83, 85, 87, 98, 
	106, 111, 113, 115, 117, 119, 124, 126, 
	128, 130, 132, 134, 137, 139, 141, 143, 
	145, 150, 152, 154, 156, 158, 160, 162, 
	167, 169, 171, 173, 175, 178, 180, 182, 
	184, 186, 191, 193, 195, 197, 199, 201, 
	203, 208, 210, 212, 214, 218, 220, 222, 
	224, 226, 228, 230, 234, 239, 242, 244, 
	247, 249, 251, 253, 255, 258, 260, 262, 
	264, 266, 268, 270, 274, 279, 282, 284, 
	287, 289, 291, 293, 295, 297, 299, 301, 
	303, 307, 312, 315, 317, 320, 322, 324, 
	326, 328, 330, 332, 334, 336, 340, 345, 
	348, 350, 353, 364, 373, 383, 387
};

static const char _hext_trans_targs[] = {
	2, 3, 0, 1, 3, 4, 0, 126, 
	3, 126, 5, 23, 24, 12, 124, 5, 
	123, 122, 122, 0, 5, 6, 5, 22, 
	22, 0, 7, 7, 0, 126, 5, 7, 
	8, 12, 7, 5, 7, 7, 7, 0, 
	9, 13, 16, 0, 0, 0, 0, 0, 
	10, 11, 0, 0, 0, 10, 126, 5, 
	12, 5, 0, 126, 0, 11, 15, 14, 
	11, 15, 14, 15, 14, 0, 0, 0, 
	17, 18, 0, 11, 17, 20, 21, 19, 
	20, 21, 19, 11, 0, 21, 19, 126, 
	5, 22, 8, 12, 22, 5, 22, 22, 
	22, 0, 126, 5, 24, 12, 5, 122, 
	122, 0, 25, 30, 48, 65, 0, 26, 
	0, 27, 0, 28, 0, 29, 0, 126, 
	5, 12, 5, 0, 31, 0, 32, 0, 
	33, 0, 34, 0, 35, 0, 36, 41, 
	0, 37, 0, 38, 0, 39, 0, 40, 
	0, 126, 5, 12, 5, 0, 42, 0, 
	43, 0, 44, 0, 45, 0, 46, 0, 
	47, 0, 126, 5, 12, 5, 0, 49, 
	0, 50, 0, 51, 0, 52, 0, 53, 
	58, 0, 54, 0, 55, 0, 56, 0, 
	57, 0, 126, 5, 12, 5, 0, 59, 
	0, 60, 0, 61, 0, 62, 0, 63, 
	0, 64, 0, 126, 5, 12, 5, 0, 
	66, 0, 67, 0, 68, 0, 69, 80, 
	109, 0, 70, 0, 71, 0, 72, 0, 
	73, 0, 74, 0, 75, 0, 76, 77, 
	75, 0, 126, 5, 12, 5, 0, 76, 
	78, 0, 79, 0, 76, 79, 0, 81, 
	0, 82, 0, 83, 0, 84, 0, 85, 
	96, 0, 86, 0, 87, 0, 88, 0, 
	89, 0, 90, 0, 91, 0, 92, 93, 
	91, 0, 126, 5, 12, 5, 0, 92, 
	94, 0, 95, 0, 92, 95, 0, 97, 
	0, 98, 0, 99, 0, 100, 0, 101, 
	0, 102, 0, 103, 0, 104, 0, 105, 
	106, 104, 0, 126, 5, 12, 5, 0, 
	105, 107, 0, 108, 0, 105, 108, 0, 
	110, 0, 111, 0, 112, 0, 113, 0, 
	114, 0, 115, 0, 116, 0, 117, 0, 
	118, 119, 117, 0, 126, 5, 12, 5, 
	0, 118, 120, 0, 121, 0, 118, 121, 
	0, 126, 5, 122, 24, 12, 122, 5, 
	122, 122, 122, 0, 126, 5, 24, 12, 
	5, 123, 122, 122, 0, 126, 5, 23, 
	24, 12, 5, 123, 122, 122, 0, 1, 
	3, 4, 0, 1, 3, 4, 0, 0
};

static const char _hext_trans_actions[] = {
	0, 0, 1, 59, 0, 59, 1, 0, 
	0, 61, 61, 61, 61, 61, 61, 61, 
	88, 91, 91, 1, 0, 0, 0, 37, 
	37, 1, 33, 33, 1, 76, 76, 0, 
	35, 76, 0, 76, 0, 0, 0, 1, 
	0, 0, 0, 1, 1, 1, 1, 1, 
	53, 55, 1, 1, 1, 0, 57, 57, 
	57, 57, 1, 71, 1, 85, 49, 49, 
	51, 0, 0, 0, 0, 1, 1, 1, 
	41, 43, 1, 43, 0, 82, 45, 45, 
	47, 0, 0, 0, 1, 0, 0, 79, 
	79, 0, 39, 79, 0, 79, 0, 0, 
	0, 1, 65, 65, 65, 65, 65, 100, 
	100, 1, 0, 0, 0, 0, 1, 0, 
	1, 0, 1, 0, 1, 0, 1, 15, 
	15, 15, 15, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 0, 0, 
	1, 0, 1, 0, 1, 0, 1, 0, 
	1, 23, 23, 23, 23, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	0, 1, 25, 25, 25, 25, 1, 0, 
	1, 0, 1, 0, 1, 0, 1, 0, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	0, 1, 27, 27, 27, 27, 1, 0, 
	1, 0, 1, 0, 1, 0, 1, 0, 
	1, 0, 1, 29, 29, 29, 29, 1, 
	0, 1, 0, 1, 0, 1, 0, 0, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 5, 1, 7, 7, 
	0, 1, 17, 17, 17, 17, 1, 9, 
	9, 1, 11, 1, 13, 0, 1, 0, 
	1, 0, 1, 0, 1, 0, 1, 0, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 5, 1, 7, 7, 
	0, 1, 19, 19, 19, 19, 1, 9, 
	9, 1, 11, 1, 13, 0, 1, 0, 
	1, 0, 1, 0, 1, 0, 1, 0, 
	1, 0, 1, 0, 1, 5, 1, 7, 
	7, 0, 1, 31, 31, 31, 31, 1, 
	9, 9, 1, 11, 1, 13, 0, 1, 
	0, 1, 0, 1, 0, 1, 0, 1, 
	0, 1, 0, 1, 0, 1, 5, 1, 
	7, 7, 0, 1, 21, 21, 21, 21, 
	1, 9, 9, 1, 11, 1, 13, 0, 
	1, 69, 69, 0, 69, 69, 0, 69, 
	0, 0, 0, 1, 67, 67, 67, 67, 
	67, 0, 103, 103, 1, 63, 63, 63, 
	63, 63, 63, 94, 97, 97, 1, 0, 
	0, 0, 1, 3, 3, 3, 1, 0
};

static const char _hext_eof_actions[] = {
	0, 106, 106, 106, 106, 106, 106, 106, 
	106, 106, 106, 106, 106, 106, 106, 106, 
	106, 106, 106, 106, 106, 106, 106, 106, 
	106, 106, 106, 106, 106, 106, 106, 106, 
	106, 106, 106, 106, 106, 106, 106, 106, 
	106, 106, 106, 106, 106, 106, 106, 106, 
	106, 106, 106, 106, 106, 106, 106, 106, 
	106, 106, 106, 106, 106, 106, 106, 106, 
	106, 106, 106, 106, 106, 106, 106, 106, 
	106, 106, 106, 106, 106, 106, 106, 106, 
	106, 106, 106, 106, 106, 106, 106, 106, 
	106, 106, 106, 106, 106, 106, 106, 106, 
	106, 106, 106, 106, 106, 106, 106, 106, 
	106, 106, 106, 106, 106, 106, 106, 106, 
	106, 106, 106, 106, 106, 106, 106, 106, 
	106, 106, 106, 106, 106, 73, 73
};

static const int hext_start = 125;
static const int hext_first_final = 125;
static const int hext_error = 0;

static const int hext_en_main = 125;


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

