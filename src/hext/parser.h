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
#include "hext/attribute.h"
#include "hext/rule.h"


namespace hext {
namespace parser {


class parse_error : public std::runtime_error
{
public:
  explicit parse_error(const char * msg);
};


/// Internal parse state used in parse_range.
struct state
{
  state();

  int indent;
  std::string tag_name;
  bool is_direct_desc;
  std::string attr_name;
  std::vector<attribute> attrs;
};

/// Use lexer to lex from begin to end, then convert tokens to vector<rule>.
std::vector<rule> parse_range(const char * begin, const char * end);

/// Read file into buffer and calls parser::parse_range.
std::vector<rule> parse_file(const std::string& path);


} // namespace parser
} // namespace hext


#endif // HEXT_PARSER_H

