#include "hext/lexer.h"


namespace hext {


lexer::lex_error::lex_error(const std::string& msg)
: std::runtime_error(msg)
{
}


lexer::lexer(const char * begin, const char * end)
: p_begin(begin),
  p(begin),
  pe(end),
  eof(end),
  cs(0)
{
  using namespace ragel;
  %%{
    machine hext;
    include "hext.rl";
    write init;
  }%%
}

std::vector<token> lexer::lex()
{
  using namespace ragel;

  std::vector<token> tokens;

  // this calls throw_error on lexing error
  %% write exec;

  return tokens;
}

void lexer::throw_error() const
{
  std::pair<size_t, size_t> pos =
    get_char_position(this->p, this->p_begin, this->pe);

  std::string char_name;
  if( this->p == this->pe )
    char_name = "[eof]";
  else if( this->p )
    char_name = get_char_name(*this->p);
  else
    char_name = "[unknown]";

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


} // namespace hext

