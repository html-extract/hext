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
  assert(this->p && this->p_begin && this->pe);

  char_pos_pair pos =
    get_char_position(this->p, this->p_begin, this->pe);

  const auto line_count = pos.first + 1;
  const auto char_count = pos.second + 1;

  std::string char_name;
  if( this->p == this->pe )
    char_name = "[eof]";
  else
    char_name = get_char_name(*this->p);

  const char * end = this->p;
  if( this->p < this->pe )
    end++;

  std::stringstream error_msg;
  error_msg << "Unexpected character '"
            << char_name
            << "' at line "
            << line_count
            << ", char "
            << char_count
            << "\n\n";

  int number_width = get_dec_number_width(line_count);
  print_with_line_numbers(this->p_begin, end, number_width, error_msg);

  size_t indent = pos.second
                + 2 /* strlen(": ") */
                + number_width;
  error_msg << std::string(indent, ' ')
            << "^ here";

  throw lex_error(error_msg.str());
}

void lexer::throw_unknown_builtin(const std::string& builtin_name) const
{
  assert(this->p && this->p_begin && this->pe);

  char_pos_pair pos =
    get_char_position(this->p, this->p_begin, this->pe);

  const auto line_count = pos.first + 1;
  const auto char_count = pos.second + 1;

  std::stringstream error_msg;
  error_msg << "Unknown builtin '"
            << builtin_name
            << "' at line "
            << line_count
            << ", char "
            << char_count
            << "\n\n";

  const char * end = this->p;
  if( this->p < this->pe )
    end++;

  int number_width = get_dec_number_width(line_count);
  print_with_line_numbers(this->p_begin, end, number_width, error_msg);

  size_t indent = pos.second
                + 2 /* strlen(": ") */
                + number_width
                - builtin_name.size();
  error_msg << std::string(indent, ' ')
            << std::string(builtin_name.size(), '^')
            << " here";

  throw lex_error(error_msg.str());
}


} // namespace hext

