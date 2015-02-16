#ifndef HEXT_TOKEN_H
#define HEXT_TOKEN_H

#include <string>


namespace hext {


enum token_id {
    TK_ERROR         = 1 << 0
  , TK_INDENT        = 1 << 1
  , TK_RULE_BEGIN    = 1 << 2
  , TK_DIRECT_DESC   = 1 << 3
  , TK_NTH_CHILD     = 1 << 4
  , TK_TAG_NAME      = 1 << 5
  , TK_BUILTIN       = 1 << 6
  , TK_ATTR_NAME     = 1 << 7
  , TK_CAP_VAR       = 1 << 8
  , TK_CAP_REGEX     = 1 << 9
  , TK_CAP_END       = 1 << 10
  , TK_MATCH_REGEX   = 1 << 11
  , TK_MATCH_LITERAL = 1 << 12
  , TK_RULE_END      = 1 << 13
  , TK_NEWLINE       = 1 << 14
  , TK_EOF           = 1 << 15
};


struct token
{
  std::string to_string() const;

  token_id tid;
  const char * begin;
  const char * end;
};


} // namespace hext


#endif // HEXT_TOKEN_H

