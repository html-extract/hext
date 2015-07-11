#include "hext/Parser.h"

#include "hext/BeginsWithTest.h"
#include "hext/Builtins.h"
#include "hext/ContainsTest.h"
#include "hext/ContainsWordsTest.h"
#include "hext/EndsWithTest.h"
#include "hext/EqualsTest.h"
#include "hext/MakeUnique.h"
#include "hext/NegateTest.h"
#include "hext/pattern/AttributeCapture.h"
#include "hext/pattern/AttributeCountMatch.h"
#include "hext/pattern/AttributeMatch.h"
#include "hext/pattern/BuiltinCapture.h"
#include "hext/pattern/BuiltinMatch.h"
#include "hext/pattern/CapturePattern.h"
#include "hext/pattern/ChildCountMatch.h"
#include "hext/pattern/MatchPattern.h"
#include "hext/pattern/NegateMatch.h"
#include "hext/pattern/NthChildMatch.h"
#include "hext/pattern/OnlyChildMatch.h"
#include "hext/pattern/TextNodeMatch.h"
#include "hext/PatternValues.h"
#include "hext/RegexTest.h"
#include "hext/RuleBuilder.h"
#include "hext/StringUtil.h"
#include "hext/ValueTest.h"

#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <algorithm>

#include <boost/optional.hpp>
#include <boost/regex/regex_traits.hpp>
#include <boost/regex/pattern_except.hpp>
#include <gumbo.h>


namespace hext {


/// Convenience macro to store the start of a token. Used within the hext
/// machine definition. Accesses local variables of `Parser::parse()`.
#define TK_START \
  tok_begin = p; \
  tok_end = nullptr;


/// Convenience macro to complete a token. Used within the hext
/// machine defintion. Accesses local variables of `Parser::parse()`.
#define TK_STOP                 \
  assert(tok_begin != nullptr); \
  assert(p != nullptr);         \
  tok_end = p;                  \
  tok = std::string(tok_begin, std::distance(tok_begin, tok_end));


/// The ragel namespace holds ragel's static data.
namespace ragel {
  /// Embed the ragel state machine.
  %%{
    machine hext;
    include "hext-machine.rl";
    write data;
  }%%
} // namespace ragel


struct Parser::Impl
{
  Impl(const char * begin, const char * end)
  : p_begin_(begin),
    p(begin),
    pe(end),
    eof(end),
    cs(0)
  {
  }

  Rule parse();

  /// Throw `SyntaxError` with an error message marking an unexpected character.
  void throw_unexpected() const;

  /// Throw `SyntaxError` with an error message marking an invalid html tag.
  void throw_invalid_tag(const std::string& tag) const;

  /// Throw `SyntaxError` with an error message marking an invalid regular
  /// expression.
  void throw_regex_error(
    std::size_t mark_len,
    boost::regex_constants::error_type e_code
  ) const;

  /// Throw `SyntaxError` with an error message complaining about a missing
  /// closing tag.
  void throw_missing_tag(HtmlTag missing) const;

  /// Throw `SyntaxError` with an error message marking an invalid closing tag.
  ///
  /// \param tag
  ///   The invalid tag name.
  ///
  /// \param expected
  ///   The next expected closing HtmlTag. If empty, a closing tag was
  ///   given but none expected.
  void throw_unexpected_tag(
    const std::string& tag,
    boost::optional<HtmlTag> expected
  ) const;

  /// Print an error at the current location within hext. Print hext with line
  /// numbers up to the unexpected character.
  ///
  /// \param uc
  ///   A pointer to the unexpected character.
  ///
  /// \param mark_len
  ///   Amount of '^' characters that are used to mark the error location up to
  ///   the unexpected character.
  void print_error_location(
    const char * uc,
    std::size_t mark_len,
    std::ostream& out
  ) const;

  /// The beginning of the hext input.
  const char * p_begin_;

  /// The current character that ragel is processing within the hext input.
  const char * p;

  /// The end of the hext input.
  const char * pe;

  /// The end of the hext input. Same as `Parser::pe`.
  const char * eof;

  /// Ragel's current state.
  int cs;
};


Parser::Parser(const char * begin, const char * end)
: impl_(MakeUnique<Impl>(begin, end))
{
}

Parser::Parser(Parser&&) = default;
Parser& Parser::operator=(Parser&&) = default;
Parser::~Parser() = default;

Rule Parser::parse()
{
  return this->impl_->parse();
}

Rule Parser::Impl::parse()
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

void Parser::Impl::throw_unexpected() const
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

  throw SyntaxError(error_msg.str());
}

void Parser::Impl::throw_invalid_tag(const std::string& tag) const
{
  std::stringstream error_msg;
  error_msg << "Unknown HTML tag '" << tag << "' ";

  auto unexpected_char = this->p - 1;
  this->print_error_location(unexpected_char, tag.size(), error_msg);

  throw SyntaxError(error_msg.str());
}

void Parser::Impl::throw_regex_error(
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

  throw SyntaxError(error_msg.str());
}

void Parser::Impl::throw_missing_tag(HtmlTag missing) const
{
  std::stringstream error_msg;
  error_msg << "Missing closing tag '</"
            << ( missing == HtmlTag::ANY
                 ? "*"
                 : gumbo_normalized_tagname(static_cast<GumboTag>(missing)) )
            << ">' ";

  this->print_error_location(this->pe, /* mark_len: */ 0, error_msg);

  throw SyntaxError(error_msg.str());
}

void Parser::Impl::throw_unexpected_tag(
  const std::string& tag,
  boost::optional<HtmlTag> expected
) const
{
  std::stringstream error_msg;
  error_msg << "Unexpected closing tag '</"
            << tag
            << ">'";

  if( expected )
  {
    error_msg << ", expected '</"
              << ( *expected == HtmlTag::ANY
                   ? "*"
                   : gumbo_normalized_tagname(static_cast<GumboTag>(*expected)) )
              << ">'";
  }

  auto mark_len = tag.size() + 2; // strlen("</")
  auto unexpected_char = this->p - 1;
  this->print_error_location(unexpected_char, mark_len, error_msg);

  throw SyntaxError(error_msg.str());
}

void Parser::Impl::print_error_location(
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

