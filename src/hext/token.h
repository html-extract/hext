#ifndef HEXT_TOKEN_H
#define HEXT_TOKEN_H


namespace hext {


enum token_id {
    TK_ERROR        = 1 << 0
  , TK_INDENT       = 1 << 1
  , TK_RULE_BEGIN   = 1 << 2
  , TK_DIRECT_DESC  = 1 << 3
  , TK_TAG_NAME     = 1 << 4
  , TK_ATTR_NAME    = 1 << 5
  , TK_ATTR_LITERAL = 1 << 6
  , TK_ATTR_CAPTURE = 1 << 7
  , TK_RULE_END     = 1 << 8
  , TK_EOF          = 1 << 9
};


struct token
{
  token_id tid;
  const char * tok_begin;
  const char * tok_end;
};


} // namespace hext


#endif // HEXT_TOKEN_H

