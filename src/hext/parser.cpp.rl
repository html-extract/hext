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

  // The line and char offset of the unexpected character
  CharPosPair pos =
    GetCharPosition(this->p, this->p_begin_, this->pe);

  // GetCharPosition's offsets are zero-based.
  const auto line_count = pos.first + 1;
  const auto char_count = pos.second + 1;

  std::string char_name;
  if( this->p == this->pe )
    char_name = "[eof]";
  else
    char_name = GetCharName(*this->p);

  std::stringstream error_msg;
  error_msg << "Unexpected character '"
            << char_name
            << "' at line "
            << line_count
            << ", char "
            << char_count
            << "\n\n";

  // We need a 'past-the-last-element' iterator.
  const char * end = this->p;

  // this->p points to the unexpected character. We want to include this
  // character when printing error location, unless it is a newline, then it
  // would just mess up the output.
  if( this->p < this->pe && *this->p != '\n' )
    end++;

  // The amount of chars needed to print the biggest line number.
  int number_width = GetDecNumberWidth(line_count);

  PrintWithLineNumbers(this->p_begin_, end, number_width, error_msg);

  // Print a visual indicator right under the unexpected character.
  // We need to know the amount of indentation required.
  // PrintWithLineNumbers prints lines like this:
  // 1: An SQL query goes into a bar,
  // 2: walks up to two tables and asks,
  // 3: 'Can I join you?'
  size_t indent = number_width // chars required to print the line number
                + 2            // ": "
                + pos.second;  // offset of the unexpected character from the
                               // beginning of the line.

  error_msg << std::string(indent, ' ')
            << "^ here";

  throw ParseError(error_msg.str());
}

void Parser::throw_unknown_token(
  const std::string& token_name,
  const std::string& token
) const
{
  // See Parser::throw_unexpected for some commentary.

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

  size_t indent = number_width
                + 2
                + pos.second
                - token.size();

  error_msg << std::string(indent, ' ')
            << std::string(token.size(), '^')
            << " here";

  throw ParseError(error_msg.str());
}


} // namespace hext

