#include "Parser.h"

#include "hext/AttributeCapture.h"
#include "hext/AttributeCountMatch.h"
#include "hext/AttributeMatch.h"
#include "hext/BeginsWithTest.h"
#include "hext/Builtins.h"
#include "hext/Capture.h"
#include "hext/ChildCountMatch.h"
#include "hext/ContainsTest.h"
#include "hext/ContainsWordsTest.h"
#include "hext/EndsWithTest.h"
#include "hext/EqualsTest.h"
#include "hext/FunctionCapture.h"
#include "hext/FunctionValueMatch.h"
#include "hext/Match.h"
#include "hext/NegateMatch.h"
#include "hext/NegateTest.h"
#include "hext/NthChildMatch.h"
#include "hext/OnlyChildMatch.h"
#include "hext/RegexTest.h"
#include "hext/TrimPipe.h"
#include "hext/ValueTest.h"

#include "PatternValues.h"
#include "StringUtil.h"

#include <vector>
#include <sstream>
#include <utility>
#include <algorithm>

#include <gumbo.h>


namespace hext {


/// Convenience macro to store the start of a token. Used within the hext
/// machine definition. Accesses local variables of Parser::parse().
#define TK_START \
  tok_begin = p; \
  tok_end = nullptr;


/// Convenience macro to complete a token. Used within the hext
/// machine definition. Accesses local variables of Parser::parse().
#define TK_STOP      \
  assert(tok_begin); \
  assert(p);         \
  tok_end = p;       \
  tok = std::string( \
    tok_begin,       \
    static_cast<std::string::size_type>(std::distance(tok_begin, tok_end)) \
  );

/// The ragel namespace holds ragel's static data.
namespace ragel {
  /// Embed the ragel state machine.
  %%{
    machine hext;
    include "hext-machine.rl";
    write data;
  }%%
} // namespace ragel


Parser::Parser(const char * begin, const char * end) noexcept
: rule_stack_()
, top_rule_(nullptr)
, p_begin_(begin)
, p(begin)
, pe(end)
, eof(end)
, cs(0)
{
}

Parser::~Parser() = default;
Parser::Parser(Parser&&) = default;
Parser& Parser::operator=(Parser&&) = default;

Rule Parser::parse()
{
  // Allow ragel to access its namespace.
  using namespace ragel;

  // Hide clang's warning -Wunused-const-variable.
  (void)hext_first_final;
  (void)hext_error;
  (void)hext_en_main;

  // When calling Parser::parse repeatedly, ensure we are always in a valid
  // state.
  this->p = this->p_begin_;
  this->rule_stack_.clear();
  this->top_rule_ = nullptr;

  // All values required to construct Matches and Captures.
  PatternValues pv;

  // tok_begin, tok_end, tok will be accessed by the macros TK_START and
  // TK_STOP.
  const char * tok_begin = nullptr;
  const char * tok_end = nullptr;
  std::string tok = "";

  // Hide warnings generated by ragel code.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wunreachable-code-break"
  %%{
    machine hext;
    include "hext-machine.rl";
    write init;
    write exec;
  }%%
#pragma GCC diagnostic pop

  // Throw error if there are missing closing tags.
  if( this->rule_stack_.size() )
    this->throw_missing_tag(this->rule_stack_.back().get_tag());

  if( this->top_rule_ )
  {
    return *this->top_rule_;
  }
  else
  {
    return Rule();
  }
}

Rule& Parser::cur_rule()
{
  assert(this->rule_stack_.size());
  return this->rule_stack_.back();
}

void Parser::push_rule()
{
  this->rule_stack_.emplace_back();
}

void Parser::pop_rule()
{
  assert(this->rule_stack_.size());
  if( this->rule_stack_.empty() )
    return;

  Rule rule = std::move(this->rule_stack_.back());
  this->rule_stack_.pop_back();

  if( this->rule_stack_.empty() )
  {
    if( this->top_rule_ )
      this->top_rule_->append_next(std::move(rule));
    else
      this->top_rule_ = std::make_unique<Rule>(std::move(rule));
  }
  else
  {
    this->rule_stack_.back().append_child(std::move(rule));
  }
}

void Parser::set_open_tag_or_throw(const std::string& tag_name)
{
  assert(this->rule_stack_.size());
  if( this->rule_stack_.empty() )
    return;

  if( tag_name.size() == 1 && tag_name[0] == '*' )
  {
    this->rule_stack_.back().set_tag(HtmlTag::ANY);
    return;
  }

  GumboTag tag = gumbo_tag_enum(tag_name.c_str());
  if( tag == GUMBO_TAG_UNKNOWN )
    this->throw_invalid_tag(tag_name);
  else
    this->rule_stack_.back().set_tag(static_cast<HtmlTag>(tag));
}

void Parser::validate_close_tag_or_throw(const std::string& tag_name)
{
  if( this->rule_stack_.empty() )
    this->throw_unexpected_tag(tag_name, /* expected no tag: */ {});

  HtmlTag expected_tag = this->rule_stack_.back().get_tag();
  if( tag_name.size() == 1 && tag_name[0] == '*' )
  {
    if( expected_tag != HtmlTag::ANY )
      this->throw_unexpected_tag(tag_name, expected_tag);
  }
  else
  {
    GumboTag given_tag = gumbo_tag_enum(tag_name.c_str());
    if( given_tag == GUMBO_TAG_UNKNOWN
        || static_cast<HtmlTag>(given_tag) != expected_tag )
      this->throw_unexpected_tag(tag_name, expected_tag);
  }
}

void Parser::throw_unexpected() const
{
  assert(this->p && this->p_begin_ && this->pe);
  assert(this->p <= this->pe && this->p >= this->p_begin_);

  std::stringstream error_msg;
  if( this->p == this->pe || !this->p )
    error_msg << "Premature termination ";
  else
    error_msg << "Unexpected character '"
              << CharName(*(this->p))
              << "' ";

  if( this->p && this->pe )
    this->print_error_location(this->p, /* mark_len: */ 1, error_msg);

  throw SyntaxError(error_msg.str());
}

void Parser::throw_invalid_tag(const std::string& tag) const
{
  std::stringstream error_msg;
  error_msg << "Unknown HTML tag '" << tag << "' ";

  auto unexpected_char = this->p - 1;
  this->print_error_location(unexpected_char, tag.size(), error_msg);

  throw SyntaxError(error_msg.str());
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

  throw SyntaxError(error_msg.str());
}

void Parser::throw_missing_tag(HtmlTag missing) const
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

void Parser::throw_unexpected_tag(
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

  error_msg << " ";

  auto mark_len = tag.size() + 2; // strlen("</")
  auto unexpected_char = this->p - 1;
  this->print_error_location(unexpected_char, mark_len, error_msg);

  throw SyntaxError(error_msg.str());
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
  auto line_count = static_cast<std::size_t>(pos.first + 1);
  auto char_count = static_cast<std::size_t>(pos.second + 1);

  if( uc == this->pe )
    out << "at end of input:\n\n";
  else
    out << "at line " << line_count
        << ", char " << char_count << ":\n\n";

  // Don't print the unexpected character if it is a newline
  if( uc == this->pe || *uc == '\n' )
    PrintNumberedLines(this->p_begin_, uc, out);
  else
    PrintNumberedLines(this->p_begin_, uc + 1, out);

  if( mark_len < 1 )
    return;

  // If there are non-ascii characters in the input, lazily bail out.
  if( std::any_of(this->p_begin_, this->pe, [](signed char c){return c < 0;}) )
    return;

  // The longest the mark can be is the length of the last line.
  mark_len = std::min(char_count, mark_len);

  // Print a visual indicator directly under the unexpected token ('^').
  // The required amount of indentation must be known.
  std::size_t indent = static_cast<std::size_t>(DecimalWidth(line_count))
                     + 2            // ": "
                     + char_count   // position of the unexpected character from
                                    // the beginning of the line.
                     - mark_len;    // the length of the '^' mark

  out << std::string(indent, ' ')
      << std::string(mark_len, '^')
      << " here\n";
}


} // namespace hext

