#include "hext/parser.h"


namespace hext {


ParseError::ParseError(const std::string& msg)
: std::runtime_error(msg)
{
}


Parser::Parser(const char * begin, const char * end)
: p_begin_(begin),
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

std::vector<Rule> Parser::parse()
{
  using namespace ragel;

  RuleBuilder rule;
  const char * tok_begin = nullptr;
  const char * tok_end = nullptr;
  std::string tok = "";
  bool rule_start = false;

  %% write exec;

  return rule.get_rules_and_reset();
}

void Parser::throw_unexpected() const
{
  assert(this->p && this->p_begin_ && this->pe);

  CharPosPair pos =
    GetCharPosition(this->p, this->p_begin_, this->pe);

  const auto line_count = pos.first + 1;
  const auto char_count = pos.second + 1;

  std::string char_name;
  if( this->p == this->pe )
    char_name = "[eof]";
  else
    char_name = GetCharName(*this->p);

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

  int number_width = GetDecNumberWidth(line_count);
  PrintWithLineNumbers(this->p_begin_, end, number_width, error_msg);

  size_t indent = pos.second
                + 2 /* strlen(": ") */
                + number_width;
  error_msg << std::string(indent, ' ')
            << "^ here";

  throw ParseError(error_msg.str());
}

void Parser::throw_unknown_token(
  const std::string& token_name,
  const std::string& token
) const
{
  assert(this->p && this->p_begin_ && this->pe);

  CharPosPair pos =
    GetCharPosition(this->p, this->p_begin_, this->pe);

  const auto line_count = pos.first + 1;
  const auto char_count = pos.second + 1;

  std::stringstream error_msg;
  error_msg << "Unknown "
            << token_name
            << " '"
            << token
            << "' at line "
            << line_count
            << ", char "
            << char_count
            << "\n\n";

  const char * end = this->p;
  if( this->p < this->pe )
    end++;

  int number_width = GetDecNumberWidth(line_count);
  PrintWithLineNumbers(this->p_begin_, end, number_width, error_msg);

  size_t indent = pos.second
                + 2 /* strlen(": ") */
                + number_width
                - token.size();
  error_msg << std::string(indent, ' ')
            << std::string(token.size(), '^')
            << " here";

  throw ParseError(error_msg.str());
}


} // namespace hext

