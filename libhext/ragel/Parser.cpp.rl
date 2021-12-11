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

#include "Parser.h"

#include "hext/AppendPipe.h"
#include "hext/AttributeCapture.h"
#include "hext/AttributeCountMatch.h"
#include "hext/AttributeMatch.h"
#include "hext/BeginsWithTest.h"
#include "hext/Builtins.h"
#include "hext/Capture.h"
#include "hext/CasePipe.h"
#include "hext/ChildCountMatch.h"
#include "hext/CollapseWsPipe.h"
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
#include "hext/PrependPipe.h"
#include "hext/RegexPipe.h"
#include "hext/RegexReplacePipe.h"
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
: stacks_()
, p_begin_(begin)
, p(begin)
, pe(end)
, eof(end)
, cs(0)
{
}

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

  // Initialize stacks with one result-stack and one work-stack.
  this->stacks_ = {{}, {}};

  // All values required to construct Matches and Captures.
  PatternValues pv;

  const char * tok_begin = nullptr;
  const char * tok_end = nullptr;
  std::string tok = "";

  // Convenience lambda to store the start of a token. Used within the hext
  // machine definition.
  auto tk_start = [this, &tok_begin, &tok_end](){
    tok_begin = this->p;
    tok_end = nullptr;
  };

  // Convenience lambda to complete a token. Used within the hext
  // machine definition.
  auto tk_stop = [this, &tok, &tok_begin, &tok_end](){
    assert(tok_begin);
    assert(this->p);
    tok_end = this->p;
    tok = std::string(
      tok_begin,
      static_cast<std::string::size_type>(std::distance(tok_begin, tok_end))
    );
  };

#ifndef _MSC_VER
  // Hide warnings generated by ragel code.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wunreachable-code-break"
#endif
  %%{
    machine hext;
    include "hext-machine.rl";
    write init;
    write exec;
  }%%
#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif

  if( this->stacks_.empty() )
  {
    // stacks_ should never be empty.
    assert(this->stacks_.size());
    return Rule();
  }

  if( this->stacks_.size() > 2 )
    // If there are more than two stacks, then a nested rule is unclosed,
    // because pop_nested() wasn't called enough times.
    this->throw_error_message("Unclosed nested rule");

  while( this->stacks_.size() && this->top_stack().empty() )
    this->stacks_.pop_back();

  if( this->stacks_.empty() )
    // No rules in input
    return Rule();

  // Throw error if there are missing closing tags.
  if( this->stacks_.size() > 1 || this->top_stack().size() > 1 )
    this->throw_missing_tag(
      this->top_stack().back().get_tag(),
      this->top_stack().back().get_tagname());

  return std::move(this->top_stack().back());
}

Rule& Parser::cur_rule()
{
  assert(this->top_stack().size());
  return this->top_stack().back();
}

std::vector<Rule>& Parser::top_stack()
{
  assert(this->stacks_.size());
  return this->stacks_.back();
}

std::vector<Rule>& Parser::previous_stack()
{
  assert(this->stacks_.size() > 1);
  return this->stacks_.at(this->stacks_.size() - 2);
}

void Parser::push_nested()
{
  if( this->top_stack().empty() )
    this->throw_error_message("Nested rules must have a parent");
  this->stacks_.emplace_back();
  this->stacks_.emplace_back();
}

void Parser::pop_nested()
{
  if( this->stacks_.empty() )
  {
    assert(this->stacks_.size());
    this->throw_unexpected();
  }

  if( !this->top_stack().empty() )
    this->throw_error_message("Closing nested rule without open");

  this->stacks_.pop_back();

  if( this->stacks_.empty() )
  {
    assert(this->stacks_.size());
    this->throw_unexpected();
  }

  if( this->top_stack().empty() )
    this->throw_error_message("Nested rules cannot be empty");

  if( this->top_stack().size() > 1 )
  {
    assert(this->top_stack().size() == 1);
    this->throw_unexpected();
  }

  auto nested_rule = std::move(this->top_stack().back());
  this->top_stack().pop_back();
  this->stacks_.pop_back();

  if( this->stacks_.empty() )
    this->throw_error_message("Closing nested rule without open");

  if( this->top_stack().empty() )
    this->throw_error_message("Nested rules must have a parent");
  else
    this->cur_rule().append_nested(std::move(nested_rule));
}

void Parser::push_rule()
{
  this->top_stack().emplace_back();
}

void Parser::pop_rule()
{
  if( this->stacks_.empty() || this->top_stack().empty() )
  {
    assert(this->stacks_.size());
    assert(this->top_stack().size());
    this->throw_unexpected();
  }

  // Collapse elements on same stack
  if( this->top_stack().size() > 1 )
  {
    Rule rule = std::move(this->top_stack().back());
    this->top_stack().pop_back();
    this->top_stack().back().append_child(std::move(rule));
  }
  else // top_stack().size() == 1
  {
    if( this->stacks_.size() < 2 )
    {
      assert(this->stacks_.size() > 1);
      this->throw_unexpected();
    }

    // Here, there is exactly one rule on the top stack. This rule is pushed
    // up one stack, to the temporary or final result.
    Rule rule = std::move(this->top_stack().back());
    this->top_stack().pop_back();

    if( this->previous_stack().empty() )
      // New top rule
      this->previous_stack().push_back(std::move(rule));
    else
      // New sibling rule
      this->previous_stack().back().append_next(std::move(rule));
  }
}

void Parser::set_open_tag_or_throw(const std::string& tag_name)
{
  assert(this->top_stack().size());
  if( this->top_stack().empty() )
    return;

  if( tag_name.size() == 1 && tag_name[0] == '*' )
  {
    this->cur_rule().set_tag(HtmlTag::ANY);
    return;
  }

  GumboTag tag = gumbo_tag_enum(tag_name.c_str());
  this->cur_rule().set_tag(static_cast<HtmlTag>(tag));

  if( tag == GUMBO_TAG_UNKNOWN )
    this->cur_rule().set_tagname(tag_name);
}

void Parser::validate_close_tag_or_throw(const std::string& tag_name)
{
  if( this->top_stack().empty() )
    this->throw_unexpected_tag(tag_name, /* expected no tag: */ {});

  HtmlTag expected_tag = this->cur_rule().get_tag();
  if( expected_tag == HtmlTag::UNKNOWN )
  {
    const auto expected_tagname = this->cur_rule().get_tagname();

    if( !expected_tagname )
    {
      assert(false);
      this->throw_unexpected_tag(tag_name, HtmlTag::UNKNOWN);
    }
    else if( expected_tagname != tag_name )
    {
      this->throw_unexpected_tag(
          tag_name, HtmlTag::UNKNOWN, expected_tagname);
    }
  }
  else if( tag_name.size() == 1 && tag_name[0] == '*' )
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

void Parser::throw_missing_tag(
  HtmlTag missing,
  std::optional<std::string> missing_tagname
) const
{
  std::stringstream error_msg;
  error_msg << "Missing closing tag '</";

  if( missing_tagname )
    error_msg << *missing_tagname;
  else
    error_msg << ( missing == HtmlTag::ANY
                   ? "*"
                   : gumbo_normalized_tagname(static_cast<GumboTag>(missing)) );

  error_msg << ">' ";

  this->print_error_location(this->pe, /* mark_len: */ 0, error_msg);

  throw SyntaxError(error_msg.str());
}

void Parser::throw_unexpected_tag(
  const std::string& tag,
  std::optional<HtmlTag> expected,
  std::optional<std::string> expected_tagname
) const
{
  std::stringstream error_msg;
  error_msg << "Unexpected closing tag '</"
            << tag
            << ">'";

  if( expected_tagname )
  {
    error_msg << ", expected '</"
              << *expected_tagname
              << ">'";
  }
  else if( expected )
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

void Parser::throw_error_message(const std::string& msg) const
{
  std::stringstream error_msg;
  error_msg << msg << " ";
  std::size_t mark_len = 1;
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

