#ifndef HEXT_TOKEN_H
#define HEXT_TOKEN_H

#include <string>


namespace hext {


enum token_id {
    TK_ERROR        = 1 << 0
  , TK_INDENT       = 1 << 1
  , TK_RULE_BEGIN   = 1 << 2
  , TK_DIRECT_DESC  = 1 << 3
  , TK_CAP_LIMIT    = 1 << 4
  , TK_TAG_NAME     = 1 << 5
  , TK_ATTR_NAME    = 1 << 6
  , TK_ATTR_LITERAL = 1 << 7
  , TK_ATTR_CAPTURE = 1 << 8
  , TK_RULE_END     = 1 << 9
  , TK_EOF          = 1 << 10
};


struct token
{
  token_id tid;
  const char * begin;
  const char * end;

  std::string to_string() const;
};


} // namespace hext


#endif // HEXT_TOKEN_H

