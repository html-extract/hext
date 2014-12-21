#ifndef HEXT_LEXER_H
#define HEXT_LEXER_H

#include <string>
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
    explicit lex_error(const std::string& msg)
    : std::runtime_error(msg) {}
  };

  lexer(const char * begin, const char * end)
  : p_begin(begin),
    p(begin),
    pe(end),
    eof(end),
    cs(0)
  {
    using namespace ragel;
    %% write init;
  }

  std::vector<token> lex()
  {
    using namespace ragel;

    std::vector<token> tokens;

    // this calls throw_error on lexing error
    %% write exec;

    return tokens;
  }

  void throw_error() const
  {
    std::pair<size_t, size_t> pos =
      get_char_position(this->p, this->p_begin, this->pe);

    std::string char_name;
    if( this->p == this->pe )
    {
      char_name = "[eof]";
    }
    else
    {
      if( this->p != nullptr )
        char_name = get_char_name(*this->p);
      else
        char_name = "[unknown]";
    }

    std::stringstream error_msg;
    error_msg << "Error at line "
              << pos.first + 1
              << ", char "
              << pos.second + 1
              << ", unexpected character '"
              << char_name
              << "'";

    throw lex_error(error_msg.str());
  }

private:
  const char * p_begin;
  const char * p;
  const char * pe;
  const char * eof;
  int cs;
};


} // namespace hext


#endif // HEXT_LEXER_H

