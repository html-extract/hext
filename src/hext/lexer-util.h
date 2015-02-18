#ifndef HEXT_LEXER_UTIL_H
#define HEXT_LEXER_UTIL_H

#include <cassert>

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


} // namespace hext


#endif // HEXT_LEXER_UTIL_H

