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

#include <boost/regex/regex_traits.hpp>
#include <boost/regex/pattern_except.hpp>


#define LX_TK_START \
  tok_begin = p;    \
  tok_end = nullptr;

#define LX_TK_STOP              \
  assert(tok_begin != nullptr); \
  tok_end = p;                  \
  tok = std::string(tok_begin, std::distance(tok_begin, tok_end));


namespace hext {


/// Clang warns (-Wweak-vtables) that a vtable for ParseError may be placed
/// in every translation unit, because ParseError doesn't have any
/// 'out-of-line virtual method definitions', where it would normally put
/// the vtable. But http://stackoverflow.com/a/23749273 suggests that this
/// is a non-issue; the linker will clean it up.
class ParseError : public std::runtime_error
{
public:
  explicit ParseError(const std::string& msg);
};


namespace ragel {
  
#line 49 "Parser.h.tmp"
static const char _hext_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 1, 9, 1, 10, 1, 
	11, 1, 12, 1, 13, 1, 14, 1, 
	15, 1, 16, 1, 17, 1, 18, 1, 
	20, 1, 22, 1, 23, 2, 1, 24, 
	2, 3, 14, 2, 5, 14, 2, 8, 
	9, 2, 10, 11, 2, 16, 19, 2, 
	16, 21, 2, 17, 19, 2, 17, 21, 
	2, 18, 21, 2, 20, 21, 3, 0, 
	1, 24
};

static const unsigned char _hext_key_offsets[] = {
	0, 0, 2, 5, 6, 19, 27, 31, 
	45, 48, 52, 56, 61, 62, 64, 66, 
	67, 70, 73, 75, 77, 78, 79, 93, 
	102, 115, 126, 138, 141
};

static const char _hext_trans_keys[] = {
	32, 35, 32, 35, 60, 10, 10, 32, 
	33, 62, 63, 9, 13, 49, 57, 65, 
	90, 97, 122, 32, 64, 9, 13, 65, 
	90, 97, 122, 65, 90, 97, 122, 10, 
	32, 45, 61, 62, 95, 9, 13, 48, 
	57, 65, 90, 97, 122, 34, 47, 123, 
	34, 47, 123, 125, 34, 47, 123, 125, 
	10, 32, 62, 9, 13, 10, 47, 92, 
	47, 92, 92, 47, 123, 125, 47, 123, 
	125, 47, 92, 47, 92, 125, 92, 10, 
	32, 45, 61, 62, 95, 9, 13, 48, 
	57, 65, 90, 97, 122, 10, 32, 62, 
	9, 13, 65, 90, 97, 122, 10, 32, 
	45, 62, 95, 9, 13, 48, 57, 65, 
	90, 97, 122, 10, 32, 62, 9, 13, 
	48, 57, 65, 90, 97, 122, 10, 32, 
	33, 62, 9, 13, 49, 57, 65, 90, 
	97, 122, 32, 35, 60, 32, 35, 60, 
	0
};

static const char _hext_single_lengths[] = {
	0, 2, 3, 1, 5, 2, 0, 6, 
	3, 4, 4, 3, 1, 2, 2, 1, 
	3, 3, 2, 2, 1, 1, 6, 3, 
	5, 3, 4, 3, 3
};

static const char _hext_range_lengths[] = {
	0, 0, 0, 0, 4, 3, 2, 4, 
	0, 0, 0, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 4, 3, 
	4, 4, 4, 0, 0
};

static const unsigned char _hext_index_offsets[] = {
	0, 0, 3, 7, 9, 19, 25, 28, 
	39, 43, 48, 53, 58, 60, 63, 66, 
	68, 72, 76, 79, 82, 84, 86, 97, 
	104, 114, 122, 131, 135
};

static const char _hext_trans_targs[] = {
	2, 3, 0, 1, 3, 4, 0, 28, 
	3, 28, 5, 23, 12, 26, 5, 25, 
	24, 24, 0, 5, 6, 5, 22, 22, 
	0, 7, 7, 0, 28, 5, 7, 8, 
	12, 7, 5, 7, 7, 7, 0, 9, 
	13, 16, 0, 0, 0, 0, 0, 10, 
	11, 0, 0, 0, 10, 28, 5, 12, 
	5, 0, 28, 0, 11, 15, 14, 11, 
	15, 14, 15, 14, 0, 0, 0, 17, 
	18, 0, 11, 17, 20, 21, 19, 20, 
	21, 19, 11, 0, 21, 19, 28, 5, 
	22, 8, 12, 22, 5, 22, 22, 22, 
	0, 28, 5, 12, 5, 24, 24, 0, 
	28, 5, 24, 12, 24, 5, 24, 24, 
	24, 0, 28, 5, 12, 5, 25, 24, 
	24, 0, 28, 5, 23, 12, 5, 25, 
	24, 24, 0, 1, 3, 4, 0, 1, 
	3, 4, 0, 0
};

static const char _hext_trans_actions[] = {
	0, 0, 1, 31, 0, 31, 1, 0, 
	0, 33, 33, 33, 33, 33, 33, 60, 
	63, 63, 1, 0, 0, 0, 9, 9, 
	1, 5, 5, 1, 48, 48, 0, 7, 
	48, 0, 48, 0, 0, 0, 1, 0, 
	0, 0, 1, 1, 1, 1, 1, 25, 
	27, 1, 1, 1, 0, 29, 29, 29, 
	29, 1, 43, 1, 57, 21, 21, 23, 
	0, 0, 0, 0, 1, 1, 1, 13, 
	15, 1, 15, 0, 54, 17, 17, 19, 
	0, 0, 0, 1, 0, 0, 51, 51, 
	0, 11, 51, 0, 51, 0, 0, 0, 
	1, 37, 37, 37, 37, 72, 72, 1, 
	41, 41, 0, 41, 0, 41, 0, 0, 
	0, 1, 39, 39, 39, 39, 0, 75, 
	75, 1, 35, 35, 35, 35, 35, 66, 
	69, 69, 1, 0, 0, 0, 1, 3, 
	3, 3, 1, 0
};

static const char _hext_eof_actions[] = {
	0, 78, 78, 78, 78, 78, 78, 78, 
	78, 78, 78, 78, 78, 78, 78, 78, 
	78, 78, 78, 78, 78, 78, 78, 78, 
	78, 78, 78, 45, 45
};

static const int hext_start = 27;
static const int hext_first_final = 27;
static const int hext_error = 0;

static const int hext_en_main = 27;


#line 49 "Parser.h.rl"

} // namespace ragel


/// Parser is responsible for parsing hext and producing Rules.
/// Parser contains the ragel state machine and shields the user from its
/// details.
class Parser
{
public:
  /// Setup ragel.
  Parser(const char * begin, const char * end);

  /// Throws ParseError on invalid input.
  std::vector<Rule> parse();

private:
  /// Print diagnostics and throw ParseError.
  void throw_unexpected() const;
  void throw_unknown_token(
    const std::string& tok,
    const std::string& tok_name
  ) const;
  void throw_regex_error(
    const std::string& tok,
    boost::regex_constants::error_type e_code
  ) const;
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

