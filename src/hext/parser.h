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
#include "hext/match-pattern.h"
#include "hext/attribute-match.h"
#include "hext/regex-match.h"
#include "hext/literal-match.h"
#include "hext/builtin-literal-match.h"
#include "hext/capture-pattern.h"
#include "hext/attribute-capture.h"
#include "hext/builtins.h"
#include "hext/builtin-capture.h"
#include "hext/rule.h"


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

  bool rule_start;
  int indent;
  std::string tag_name;
  bool is_direct_desc;
  bool is_closed;
  int cap_limit;
  bool is_builtin;
  std::string attr_name;
  std::string cap_var;
  std::string cap_regex;
  std::vector<std::unique_ptr<match_pattern>> matchp;
  std::vector<std::unique_ptr<capture_pattern>> capturep;
};

/// Use lexer to lex from begin to end, then convert tokens to vector<rule>.
std::vector<rule> parse_range(const char * begin, const char * end);

/// Read file into buffer and calls parser::parse_range.
std::vector<rule> parse_file(const std::string& path);


} // namespace parser
} // namespace hext


#endif // HEXT_PARSER_H

