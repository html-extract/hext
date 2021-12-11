// Copyright 2015-2021 Thomas Trapp
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
#include <optional>
#include <ostream>
#include <string>
#include <vector>

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

  /// Returns a reference for the topmost rule on the rule stack.
  Rule& cur_rule();

  /// Returns a reference for the topmost stack.
  std::vector<Rule>& top_stack();

  /// Returns a reference for the stack beneath the topmost stack.
  std::vector<Rule>& previous_stack();

  /// Creates a new rule on the topmost stack.
  void push_rule();

  /// Appends the topmost rule to the rule tree.
  void pop_rule();

  /// Increases the depth of the rule stack by two.
  void push_nested();

  /// Decreases the depth of the rule stack by two. Appends rules to
  /// the rule tree.
  void pop_nested();

  /// Sets the HtmlTag for the top most rule or throws an exception
  /// if tag_name is not a valid tag.
  void set_open_tag_or_throw(const std::string& tag_name);

  /// Throws an exception if tag_name is not a valid HTML tag or if tag_name
  /// does not equal the tag from the top most rule.
  void validate_close_tag_or_throw(const std::string& tag_name);

  /// Throws SyntaxError with an error message marking an unexpected character.
  [[noreturn]]
  void throw_unexpected() const;

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
  /// @param         missing:  The HTML tag that is missing.
  /// @param missing_tagname:  The missing closing custom tag name.
  [[noreturn]]
  void throw_missing_tag(
      HtmlTag                    missing,
      std::optional<std::string> missing_tagname) const;

  /// Throws SyntaxError with an error message marking an invalid closing tag.
  ///
  /// @param              tag:  A string containing the invalid HTML closing
  ///                           tag.
  /// @param         expected:  The next expected closing HtmlTag. If empty, a
  ///                           closing tag was given but none expected.
  /// @param expected_tagname:  The next expected closing custom tag name.
  [[noreturn]]
  void throw_unexpected_tag(
      const std::string&         tag,
      std::optional<HtmlTag>     expected,
      std::optional<std::string> expected_tagname = std::nullopt) const;

  /// Throws SyntaxError with an error message.
  ///
  /// @param msg:  The error message.
  [[noreturn]] void throw_error_message(const std::string& msg) const;

  /// Prints an error at the current location within hext. Prints hext with line
  /// numbers up to the unexpected character.
  ///
  /// @param       uc:  A pointer to the unexpected character.
  /// @param mark_len:  The length of the error marker.
  /// @param      out:  Where to put the error message.
  void print_error_location(const char *  uc,
                            std::size_t   mark_len,
                            std::ostream& out) const;

  /// A stack of stacks containing Rules.
  ///
  /// Each nesting of rules has two stacks:
  /// * result-stack: Holds finished rules.
  /// * work-stack: Rules are constructed on the work-stack until
  ///   they are complete and can be moved to the preceding result-stack.
  std::vector<std::vector<Rule>> stacks_;

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

