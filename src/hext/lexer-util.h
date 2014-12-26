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
  tok.tok_begin = p;       \
  tok.tok_end = nullptr;   \
  tokens.push_back(tok);

#define LX_TK_STOP           \
  assert(tokens.size() > 0); \
  tokens.back().tok_end = p;


namespace hext {


std::string get_char_name(char c);

std::pair<size_t, size_t> get_char_position(
  const char * c,
  const char * begin,
  const char * end
);


} // namespace hext


#endif // HEXT_LEXER_UTIL_H

