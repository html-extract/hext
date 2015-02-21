#ifndef HEXT_PARSER_H
#define HEXT_PARSER_H

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <utility>

#include "hext/string-util.h"
#include "hext/builtins.h"
#include "hext/rule.h"
#include "hext/rule-builder.h"


#define LX_TK_START \
  tok_begin = p;    \
  tok_end = nullptr;

#define LX_TK_STOP              \
  assert(tok_begin != nullptr); \
  tok_end = p;                  \
  tok = std::string(tok_begin, std::distance(tok_begin, tok_end));


namespace hext {


/// Clang warns (-Wweak-vtables) that a vtable for parse_error may be placed
/// in every translation unit, because parse_error doesn't have any
/// 'out-of-line virtual method definitions', where it would normally put
/// the vtable. But http://stackoverflow.com/a/23749273 suggests that this
/// is a non-issue; the linker will clean it up.
class parse_error : public std::runtime_error
{
public:
  explicit parse_error(const std::string& msg);
};


namespace ragel {
  %%{
    machine hext;
    include "hext.rl";
    write data;
  }%%
} // namespace ragel


/// parser is responsible for parsing hext and producing rules.
/// parser contains the ragel state machine and shields the user from its
/// details.
class parser
{
public:
  /// Setup ragel.
  parser(const char * begin, const char * end);

  /// Throws parse_error on invalid input.
  std::vector<rule> parse();

private:
  /// Print diagnostics and throw parse_error.
  void throw_unexpected() const;
  void throw_unknown_builtin(const std::string& builtin_name) const;

  /// A pointer to the beginning of the overall input is needed to provide
  /// good error diagnostics.
  const char * p_begin;

  /// ragel's runtime state
  const char * p;
  const char * pe;
  const char * eof;
  int cs;
};


} // namespace hext


#endif // HEXT_PARSER_H

