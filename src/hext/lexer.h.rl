#ifndef HEXT_LEXER_H
#define HEXT_LEXER_H

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <utility>

#include "hext/token.h"
#include "hext/lexer-util.h"


namespace hext {


namespace ragel {
  %%{
    machine hext;
    include "hext.rl";
    write data;
  }%%
} // namespace ragel


class lexer
{
public:
  class lex_error : public std::runtime_error
  {
  public:
    explicit lex_error(const std::string& msg);
  };

  lexer(const char * begin, const char * end);

  std::vector<token> lex();

  void throw_error() const;

private:
  const char * p_begin;
  const char * p;
  const char * pe;
  const char * eof;
  int cs;
};


} // namespace hext


#endif // HEXT_LEXER_H

