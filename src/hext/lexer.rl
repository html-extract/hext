#ifndef HEXT_LEXER_H
#define HEXT_LEXER_H

#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <cassert>
#include <stdexcept>

#include "hext/token.h"

#define LX_TK_START(tk_id) \
  token tok;               \
  tok.tid = tk_id;         \
  tok.tok_begin = p;       \
  tok.tok_end = nullptr;   \
  tokens.push_back(tok);

#define LX_TK_STOP                          \
  assert(tokens.size() > 0);                \
  tokens.at(tokens.size() - 1).tok_end = p;

namespace hext {


namespace ragel {
  %%{
    machine hext;
    include "hext.rl";
    write data;
  }%%
}


class lexer
{
public:
  class lex_error : public std::runtime_error
  {
  public:
    lex_error(const char * msg)
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

    // this throws on lexing error
    %% write exec;

    return tokens;
  }

  void print_error()
  {
    typedef
      std::iterator_traits<std::string::const_iterator>::difference_type
      iter_diff_type;

    std::string all_to_error(this->p_begin, this->p);
    iter_diff_type line_nr =
      std::count(all_to_error.begin(), all_to_error.end(), '\n');

    size_t char_nr = 0;
    size_t line_offset = 0;
    if( line_nr )
    {
      line_offset = all_to_error.find_last_of('\n');
      if( line_offset == std::string::npos )
        line_offset = 1;
      // move past \n
      line_offset += 1;
    }
    char_nr = std::distance(this->p_begin, this->p) - line_offset;

    std::string error_token;
    if( *p == '\n' )
      error_token = "[newline]";
    else if( *p == ' ' )
      error_token = "[space]";
    else 
      error_token = *p;

    std::cerr << "Error at line "
              << line_nr + 1
              << ", char "
              << char_nr + 1
              << ", unexpected character '"
              << error_token
              << "'\n";
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

