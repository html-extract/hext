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
  %%{
    machine hext;
    include "hext-machine.rl";
    write data;
  }%%
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
