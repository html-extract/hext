#ifndef HEXT_LEXER_UTIL_H
#define HEXT_LEXER_UTIL_H

#include <cassert>
#include <cctype>
#include <string>
#include <utility>
#include <algorithm>
#include <iterator>

#include "hext/token.h"


#define LX_TK_START(tk_id) \
  token tok;               \
  tok.tid = tk_id;         \
  tok.begin = p;           \
  tok.end = nullptr;       \
  tokens.push_back(tok);

#define LX_TK_STOP           \
  assert(tokens.size() > 0); \
  tokens.back().end = p;


namespace hext {


/// Returns a visual representation for every char, including control
/// characters like the nullbyte.
/// Used in error reporting.
std::string get_char_name(char c);

/// Returns a pair<line_number, character_number> for the position of c in
/// the range from begin to end. Numbering is one-based.
/// Used in error reporting.
std::pair<size_t, size_t> get_char_position(
  const char * c,
  const char * begin,
  const char * end
);


} // namespace hext


#endif // HEXT_LEXER_UTIL_H

