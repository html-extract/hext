#ifndef HEXT_PARSER_H
#define HEXT_PARSER_H

#include <cassert>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <stdexcept>

#include "hext/token.h"
#include "hext/lexer.h"
#include "hext/pattern/attr-test.h"
#include "hext/pattern/literal-test.h"
#include "hext/pattern/regex-test.h"
#include "hext/pattern/match-pattern.h"
#include "hext/pattern/attribute-match.h"
#include "hext/pattern/builtin-match.h"
#include "hext/pattern/capture-pattern.h"
#include "hext/pattern/attribute-capture.h"
#include "hext/pattern/builtin-capture.h"
#include "hext/builtins.h"
#include "hext/make-unique.h"
#include "hext/rule.h"
#include "hext/rule-builder.h"


namespace hext {
namespace parser {


/// clang: warning: 'parse_error' has no out-of-line virtual method
/// definitions; its vtable will be emitted in every translation
/// unit [-Wweak-vtables]
/// This warning can be ignored, see comment above class lex_error.
class parse_error : public std::runtime_error
{
public:
  explicit parse_error(const std::string& msg);
};


/// Internal parse state used in parse_range.
struct state
{
  state();
  ~state();

  bool rule_start;
  int indent;
  bi::builtin_func_ptr bf;
  std::string attr_name;
  std::string cap_var;
  std::string cap_regex;
};

std::unique_ptr<match_pattern>
create_match_pattern(const token& tok, const state& st);

/// Use lexer to lex from begin to end, then convert tokens to vector<rule>.
std::vector<rule> parse_range(const char * begin, const char * end);

/// Read file into buffer and call parser::parse_range.
std::vector<rule> parse_file(const std::string& path);


} // namespace parser
} // namespace hext


#endif // HEXT_PARSER_H

