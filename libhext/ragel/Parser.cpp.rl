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

Rule Parser::parse()
{
  // Allow ragel to access its namespace.
  using namespace ragel;

  // When calling Parser::parse repeatedly, ensure we are always in a valid
  // state.
  this->p = this->p_begin_;

  // Provide shortcut to keep hext-machine's code smaller.
  typedef NthChildMatch::OffsetOf NthOff;

  // In the hext-machine, the rule tree will be constructed with a RuleBuilder.
  RuleBuilder builder;

  // The rule that is currently being built.
  Rule rule;

  // All values required to construct match and capture patterns.
  PatternValues pv;

  // These variables will be accessed by the macros TK_START and TK_STOP.
  const char * tok_begin = nullptr;
  const char * tok_end = nullptr;
  std::string tok = "";

  %%{
    machine hext;
    include "hext-machine.rl";
    write init;
    write exec;
  }%%

  // Throw error if there are missing closing tags.
  if( auto expected_tag = builder.get_expected_tag() )
    this->throw_missing_tag(*expected_tag);

  return std::move(builder.take_rule_tree());
}

void Parser::throw_unexpected() const
{
  assert(this->p && this->p_begin_ && this->pe);
  assert(this->p <= this->pe && this->p >= this->p_begin_);

  if( !this->p || !this->pe )
    return;

  std::stringstream error_msg;
  if( this->p == this->pe )
  {
    error_msg << "Premature termination ";
  }
  else
  {
    error_msg << "Unexpected character '"
              << CharName(*(this->p))
              << "' ";
  }

  this->print_error_location(this->p, /* mark_len: */ 1, error_msg);

  throw ParseError(error_msg.str());
}

void Parser::throw_invalid_tag(const std::string& tag) const
{
  std::stringstream error_msg;
  error_msg << "Unknown HTML tag '" << tag << "' ";

  auto unexpected_char = this->p - 1;
  this->print_error_location(unexpected_char, tag.size(), error_msg);

  throw ParseError(error_msg.str());
}

void Parser::throw_regex_error(
  std::size_t mark_len,
  boost::regex_constants::error_type e_code
) const
{
  std::stringstream error_msg;
  error_msg << "In regular expression ";

  auto unexpected_char = this->p - 1;
  this->print_error_location(unexpected_char, mark_len, error_msg);

  // regex_error::what() not only contains an error message, but also adds the
  // error location. Therefore we use regex_traits::error_string to get a
  // shorter error description.
  boost::regex_traits<boost::regex::value_type> traits;
  error_msg << "\nError: "
            << traits.error_string(e_code);

  throw ParseError(error_msg.str());
}

void Parser::throw_missing_tag(GumboTag missing) const
{
  std::stringstream error_msg;
  error_msg << "Missing closing tag '</"
            << ( missing == GUMBO_TAG_UNKNOWN
                ? "*" : gumbo_normalized_tagname(missing) )
            << ">' ";

  this->print_error_location(this->pe, /* mark_len: */ 0, error_msg);

  throw ParseError(error_msg.str());
}

void Parser::throw_unexpected_tag(
  const std::string& tag,
  boost::optional<GumboTag> expected
) const
{
  std::stringstream error_msg;
  error_msg << "Unexpected closing tag '</"
            << tag
            << ">'";

  if( expected )
  {
    error_msg << ", expected '</"
              << ( *expected == GUMBO_TAG_UNKNOWN
                  ? "*" : gumbo_normalized_tagname(*expected) )
              << ">'";
  }

  auto mark_len = tag.size() + 2; // strlen("</")
  auto unexpected_char = this->p - 1;
  this->print_error_location(unexpected_char, mark_len, error_msg);

  throw ParseError(error_msg.str());
}

void Parser::print_error_location(
  const char * uc,
  std::size_t mark_len,
  std::ostream& out
) const
{
  assert(uc && this->p_begin_ && this->pe);
  assert(uc <= this->pe && uc >= this->p_begin_);
  if( !uc || !this->p_begin_ || !this->pe || uc > this->pe )
    return;

  // The zero-based line and char offset of the unexpected character
  CharPosPair pos = CharPosition(this->p_begin_, uc);

  if( uc == this->pe )
  {
    out << "at end of input:\n\n";
  }
  else
  {
    out << "at line "
        << pos.first + 1 // line_count
        << ", char "
        << pos.second + 1 // char_count
        << ":\n\n";
  }

  // The amount of chars needed to print the biggest line number.
  int number_width = DecimalWidth(static_cast<int>(pos.first + 1));

  // Don't print the unexpected character if it is a newline
  if( uc == this->pe || *uc == '\n' )
    PrintWithLineNumbers(this->p_begin_, uc, number_width, out);
  else
    PrintWithLineNumbers(this->p_begin_, uc + 1, number_width, out);

  if( mark_len < 1 )
    return;

  // If there are non-ascii characters in the input, lazily bail out.
  if( std::any_of(this->p_begin_, this->pe, [](signed char c){return c < 0;}) )
    return;

  // The longest the mark can be is the length of the last line.
  mark_len = std::min(pos.second + 1, static_cast<CharPosType>(mark_len));

  // Print a visual indicator directly under the unexpected token ('^').
  // The required amount of indentation must be known.
  // PrintWithLineNumbers prints lines like this:
  // 1: An SQL query goes into a bar,
  // 2: walks up to two tables and asks,
  // 3: 'Can I join you?'
  std::size_t indent = number_width // chars required to print the line number
                     + 2            // ": "
                     + pos.second+1 // position of the unexpected character from
                                    // the beginning of the line.
                     - mark_len;    // the length of the '^' mark

  out << std::string(indent, ' ')
      << std::string(mark_len, '^')
      << " here\n";
}


} // namespace hext

