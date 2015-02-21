#include "hext/lexer.h"


namespace hext {


parse_error::parse_error(const std::string& msg)
: std::runtime_error(msg)
{
}


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

std::vector<rule> lexer::lex()
{
  using namespace ragel;

  rule_builder rule;
  const char * tok_begin = nullptr;
  const char * tok_end = nullptr;
  std::string tok = "";
  bool rule_start = false;

  // this calls throw_error on lexing error
  %% write exec;

  return rule.get_rules_and_reset();
}

void lexer::throw_unexpected() const
{
  char_pos_pair pos =
    get_char_position(this->p, this->p_begin, this->pe);

  std::string char_name;
  if( this->p == this->pe )
    char_name = "[eof]";
  else if( this->p )
    char_name = get_char_name(*this->p);
  else
    char_name = "[unknown]";

  std::stringstream error_msg;
  error_msg << "Unexpected character '"
            << char_name
            << "' at line "
            << pos.first + 1
            << ", char "
            << pos.second + 1;

  throw lex_error(error_msg.str());
}

void lexer::throw_unknown_builtin(const std::string& builtin_name) const
{
  char_pos_pair pos =
    get_char_position(this->p, this->p_begin, this->pe);

  std::stringstream error_msg;
  error_msg << "Unknown builtin '"
            << builtin_name
            << "' at line "
            << pos.first + 1
            << ", char "
            << pos.second + 1;

  throw lex_error(error_msg.str());
}


} // namespace hext

