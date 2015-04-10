#include "hext/Parser.h"


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
}

std::unique_ptr<Rule> Parser::parse(Option flags)
{
  // Ragel generates state machines in plain C and knows nothing about
  // namespaces.
  using namespace ragel;

  // When calling Parser::parse repeatedly, ensure we are always in a valid
  // state.
  this->p = this->p_begin_;

  // Provide shortcut to keep hext-machine's code smaller.
  typedef NthChildMatch::OffsetOf NthOff;

  // In the hext-machine, rules will be constructed with a RuleBuilder.
  RuleBuilder rule(flags);

  // Same with patterns.
  PatternBuilder& pattern = rule.pattern();

  // These variables will be accessed by the macros TK_START and TK_STOP.
  const char * tok_begin = nullptr;
  const char * tok_end = nullptr;
  std::string tok = "";

  // A flag to tell whether we are currently parsing a rule.
  bool rule_start = false;

  %%{
    machine hext;
    include "hext-machine.rl";
    write init;
    write exec;
  }%%

  return rule.take_rule();
}

void Parser::throw_unexpected() const
{
  assert(this->p && this->p_begin_ && this->pe);

  std::stringstream error_msg;
  error_msg << "Unexpected character '"
            << ( this->p >= this->pe ? "[eof]" : GetCharName(*this->p) )
            << "' ";
  this->print_error_location(0, error_msg);

  throw ParseError(error_msg.str());
}

void Parser::throw_unknown_token(
  const std::string& tok,
  const std::string& tok_name
) const
{
  assert(this->p && this->p_begin_ && this->pe);

  std::stringstream error_msg;
  error_msg << "Unknown " << tok_name << " '" << tok << "' ";
  this->print_error_location(tok.size(), error_msg);

  throw ParseError(error_msg.str());
}

void Parser::throw_regex_error(
  std::string::size_type mark_len,
  boost::regex_constants::error_type e_code
) const
{
  assert(this->p && this->p_begin_ && this->pe);

  std::stringstream error_msg;
  error_msg << "In regular expression ";
  this->print_error_location(mark_len, error_msg);

  // regex_error::what() not only contains an error message, but also adds the
  // error location. Therefore we use regex_traits::error_string to get a
  // shorter error description.
  boost::regex_traits<boost::regex::value_type> traits;
  error_msg << "\n\nError: "
            << traits.error_string(e_code);

  throw ParseError(error_msg.str());
}

void Parser::throw_error(
  const std::string& error_msg,
  std::string::size_type mark_len
) const
{
  assert(this->p && this->p_begin_ && this->pe);

  std::stringstream error_msg_stream;
  error_msg_stream << error_msg << ", ";
  this->print_error_location(mark_len, error_msg_stream);

  throw ParseError(error_msg_stream.str());
}

void Parser::print_error_location(
  std::string::size_type mark_len,
  std::ostream& out
) const
{
  assert(this->p && this->p_begin_ && this->pe);

  // The zero-based line and char offset of the unexpected character.
  CharPosPair pos =
    GetCharPosition(this->p, this->p_begin_, this->pe);

  out << "at line "
      << pos.first + 1 // line_count
      << ", char "
      << pos.second + 1 // char_count
      << ": "
      << "\n\n";

  // We need a 'past-the-last-element' iterator.
  const char * end = this->p;

  // this->p points to the unexpected character. We want to include this
  // character when printing error location, unless it is a newline, then it
  // would just mess up the output.
  if( this->p < this->pe && *this->p != '\n' )
    end++;

  // The amount of chars needed to print the biggest line number.
  // If line_count is bigger than INT_MAX the only thing that breaks is the
  // formatting of output.
  int number_width = GetDecNumberWidth(static_cast<int>(pos.first + 1));

  PrintWithLineNumbers(this->p_begin_, end, number_width, out);

  // The longest the mark can be is the length of the last line.
  mark_len = std::min(pos.second, static_cast<CharPosType>(mark_len));

  // Print a visual indicator right under the unexpected token.
  // We need to know the amount of indentation required.
  // PrintWithLineNumbers prints lines like this:
  // 1: An SQL query goes into a bar,
  // 2: walks up to two tables and asks,
  // 3: 'Can I join you?'
  std::size_t indent = number_width // chars required to print the line number
                     + 2            // ": "
                     + pos.second   // offset of the unexpected character from
                                    // the beginning of the line.
                     - mark_len;    // the length of the '^' mark

  if( mark_len < 1 )
    mark_len = 1;

  out << std::string(indent, ' ')
      << std::string(mark_len, '^')
      << " here";
}


} // namespace hext

