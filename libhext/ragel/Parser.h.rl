#ifndef HEXT_PARSER_H_INCLUDED
#define HEXT_PARSER_H_INCLUDED

#include "hext/Builtins.h"
#include "hext/MakeUnique.h"
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
#include "hext/pattern/TextNodeMatch.h"
#include "hext/PatternValues.h"
#include "hext/Rule.h"
#include "hext/RuleBuilder.h"
#include "hext/StringUtil.h"
#include "hext/test/BeginsWith.h"
#include "hext/test/Contains.h"
#include "hext/test/ContainsWord.h"
#include "hext/test/EndsWith.h"
#include "hext/test/Equals.h"
#include "hext/test/Negate.h"
#include "hext/test/NotNull.h"
#include "hext/test/Regex.h"
#include "hext/test/ValueTest.h"

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <memory>

#include <boost/optional.hpp>
#include <boost/regex/regex_traits.hpp>
#include <boost/regex/pattern_except.hpp>
#include <gumbo.h>


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


namespace hext {


/// ParseError is a custom exception class thrown for all errors that occur
/// while parsing hext.
/// Note: Clang warns (-Wweak-vtables) that a vtable for ParseError may be
/// placed in every translation unit, because ParseError doesn't have any
/// 'out-of-line virtual method definitions', where it would normally put
/// the vtable. But http://stackoverflow.com/a/23749273 suggests that this
/// is a non-issue; the linker will clean it up.
class ParseError : public std::runtime_error
{
public:
  explicit ParseError(const std::string& msg);
};


/// The ragel namespace holds ragel's static data.
namespace ragel {
  /// Embed the ragel state machine.
  %%{
    machine hext;
    include "hext-machine.rl";
    write data;
  }%%
} // namespace ragel


/// Parser is responsible for parsing hext and producing Rules.
class Parser
{
public:
  /// Construct a Parser to parse hext rule definitions described in range
  /// `begin` to `end`. Pointers must stay valid until the last call to
  /// `Parser::parse()`.
  Parser(const char * begin, const char * end);

  /// Parse hext and return the top level Rule. Throw `ParseError` on invalid
  /// input.
  std::unique_ptr<Rule> parse();

private:
  /// Throw `ParseError` with an error message marking an unexpected character.
  void throw_unexpected() const;

  /// Throw `ParseError` with an error message marking an invalid html tag.
  void throw_invalid_tag(const std::string& tag) const;

  /// Throw `ParseError` with an error message marking an invalid regular
  /// expression.
  void throw_regex_error(
    std::size_t mark_len,
    boost::regex_constants::error_type e_code
  ) const;

  /// Throw `ParseError` with an error message complaining about a missing
  /// closing tag.
  void throw_missing_tag(GumboTag missing) const;

  /// Throw `ParseError` with an error message marking an invalid closing tag.
  ///
  /// \param tag
  ///   The invalid tag name.
  ///
  /// \param expected
  ///   The next expected closing GumboTag. If empty, a closing tag was
  ///   given but none expected.
  void throw_unexpected_tag(
    const std::string& tag,
    boost::optional<GumboTag> expected
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


} // namespace hext


#endif // HEXT_PARSER_H_INCLUDED

