// Copyright 2015-2017 Thomas Trapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef HEXT_PARSER_H_INCLUDED
#define HEXT_PARSER_H_INCLUDED

#include "hext/HtmlTag.h"
#include "hext/Rule.h"
#include "hext/SyntaxError.h"

#include <cstddef>
#include <memory>
#include <optional>
#include <ostream>
#include <string>

#include <boost/regex/regex_traits.hpp>
#include <boost/regex/pattern_except.hpp>


namespace hext {


/// Parses a string containing hext rule definitions.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   std::string hext_str("<a href:link />");
///   Parser p(hext_str.begin(), hext_str.end());
///   try {
///     Rule rule = p.parse();
///     // ... do sth. with rule ...
///   } catch( SyntaxError& e ) {
///     // e.what() will contain a detailed error message.
///   }
/// ~~~~~~~~~~~~~
class Parser
{
public:
  /// Constructs a Parser to parse hext rule definitions contained in
  /// range [begin, end). Pointers are non-owning and must stay valid until the
  /// last call to Parser::parse().
  Parser(const char * begin, const char * end) noexcept;

  /// Parses hext rule definition from the given range and returns the top level
  /// Rule. Throws SyntaxError with a detailed error message on invalid input.
  ///
  /// @throws SyntaxError
  Rule parse();

private:
  Parser(const Parser&) = delete;
  Parser& operator=(const Parser&) = delete;

  /// Returns a reference for the top most rule on the rule stack.
  Rule& cur_rule();

  /// Pushes a rule onto the rule stack.
  void push_rule();

  /// Pops a rule from the rule stack and appends it to top_rule_.
  void pop_rule();

  /// Sets the HtmlTag for the top most rule or throws an exception
  /// if tag_name is not a valid tag.
  void set_open_tag_or_throw(const std::string& tag_name);

  /// Throws an exception if tag_name is not a valid HTML tag or if tag_name
  /// does not equal the tag from the top most rule.
  void validate_close_tag_or_throw(const std::string& tag_name);

  /// Throws SyntaxError with an error message marking an unexpected character.
  [[noreturn]]
  void throw_unexpected() const;

  /// Throws SyntaxError with an error message marking an invalid HTML tag.
  ///
  /// @param tag:  A string containing the name of an invalid HTML tag.
  [[noreturn]]
  void throw_invalid_tag(const std::string& tag) const;

  /// Throws SyntaxError with an error message marking an invalid regular
  /// expression.
  ///
  /// @param mark_len:  The length of the error marker.
  /// @param   e_code:  The error code given by boost::regex.
  [[noreturn]]
  void throw_regex_error(std::size_t                        mark_len,
                         boost::regex_constants::error_type e_code) const;

  /// Throws SyntaxError with an error message complaining about a missing
  /// closing tag.
  ///
  /// @param missing:  The HTML tag that was expected.
  [[noreturn]]
  void throw_missing_tag(HtmlTag missing) const;

  /// Throws SyntaxError with an error message marking an invalid closing tag.
  ///
  /// @param      tag: A string containing the invalid HTML closing tag.
  /// @param expected: The next expected closing HtmlTag. If empty, a closing
  ///                  tag was given but none expected.
  [[noreturn]]
  void throw_unexpected_tag(const std::string&     tag,
                            std::optional<HtmlTag> expected) const;

  /// Prints an error at the current location within hext. Prints hext with line
  /// numbers up to the unexpected character.
  ///
  /// @param       uc:  A pointer to the unexpected character.
  /// @param mark_len:  The length of the error marker.
  /// @param      out:  Where to put the error message.
  void print_error_location(const char *  uc,
                            std::size_t   mark_len,
                            std::ostream& out) const;

  /// A stack containing Rules that have not yet been appended to top_rule_
  /// while parsing.
  std::vector<Rule> rule_stack_;

  /// The current top rule.
  std::unique_ptr<Rule> top_rule_;

  /// The beginning of the hext input as given in the constructor.
  const char * p_begin_;

  /// The current character that ragel is processing within the hext input.
  const char * p;

  /// The end of the hext input as given in the constructor.
  const char * pe;

  /// The end of the hext input. Same as Parser::pe.
  const char * eof;

  /// Ragel's current state.
  int cs;
};


} // namespace hext


#endif // HEXT_PARSER_H_INCLUDED

