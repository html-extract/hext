// This file was generated from Parser.cpp.rl.

#line 1 "Parser.cpp.rl"
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

std::unique_ptr<Rule> Parser::parse()
{
  // Ragel generates state machines in plain C and knows nothing about
  // namespaces.
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

  
#line 53 "Parser.cpp.tmp"
	{
	cs = hext_start;
	}

#line 58 "Parser.cpp.tmp"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_keys = _hext_trans_keys + _hext_key_offsets[cs];
	_trans = _hext_index_offsets[cs];

	_klen = _hext_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _hext_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	cs = _hext_trans_targs[_trans];

	if ( _hext_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _hext_actions + _hext_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 7 "hext-machine.rl"
	{
  this->throw_unexpected();
}
	break;
	case 1:
#line 16 "hext-machine.rl"
	{ pv.nth = {2, 0}; }
	break;
	case 2:
#line 19 "hext-machine.rl"
	{ pv.nth = {2, 1}; }
	break;
	case 3:
#line 23 "hext-machine.rl"
	{ TK_START; }
	break;
	case 4:
#line 24 "hext-machine.rl"
	{ TK_STOP; pv.nth = {0, std::stoi(tok)}; }
	break;
	case 5:
#line 27 "hext-machine.rl"
	{ pv.nth = {pv.nth.second, 0}; }
	break;
	case 6:
#line 29 "hext-machine.rl"
	{ TK_START; }
	break;
	case 7:
#line 30 "hext-machine.rl"
	{ TK_STOP; pv.nth.second = std::stoi(tok); }
	break;
	case 8:
#line 39 "hext-machine.rl"
	{ rule.add_match_pattern<ChildCountMatch>(0); }
	break;
	case 9:
#line 44 "hext-machine.rl"
	{ TK_START; }
	break;
	case 10:
#line 45 "hext-machine.rl"
	{ TK_STOP; rule.add_match_pattern<ChildCountMatch>(std::stoi(tok)); }
	break;
	case 11:
#line 51 "hext-machine.rl"
	{ TK_START; }
	break;
	case 12:
#line 52 "hext-machine.rl"
	{ TK_STOP; rule.add_match_pattern<AttributeCountMatch>(std::stoi(tok)); }
	break;
	case 13:
#line 57 "hext-machine.rl"
	{ rule.add_match_pattern<NthChildMatch>(pv.nth); }
	break;
	case 14:
#line 61 "hext-machine.rl"
	{ rule.add_match_pattern<NthChildMatch>(pv.nth, NthOff::Back); }
	break;
	case 15:
#line 65 "hext-machine.rl"
	{ rule.add_match_pattern<NthChildMatch>(pv.nth, NthOff::Front, rule.get_tag()); }
	break;
	case 16:
#line 69 "hext-machine.rl"
	{ rule.add_match_pattern<NthChildMatch>(0, 1); }
	break;
	case 17:
#line 73 "hext-machine.rl"
	{ rule.add_match_pattern<NthChildMatch>(0, 1, NthOff::Front, rule.get_tag()); }
	break;
	case 18:
#line 77 "hext-machine.rl"
	{ rule.add_match_pattern<NthChildMatch>(0, 1, NthOff::Back); }
	break;
	case 19:
#line 81 "hext-machine.rl"
	{ rule.add_match_pattern<NthChildMatch>(0, 1, NthOff::Back, rule.get_tag()); }
	break;
	case 20:
#line 85 "hext-machine.rl"
	{ rule.add_match_pattern<NthChildMatch>(pv.nth, NthOff::Back, rule.get_tag()); }
	break;
	case 21:
#line 88 "hext-machine.rl"
	{ rule.add_match_pattern<NthChildMatch>(0, 1);
                    rule.add_match_pattern<NthChildMatch>(0, 1, NthOff::Back); }
	break;
	case 22:
#line 92 "hext-machine.rl"
	{ rule.add_match_pattern<TextNodeMatch>(); }
	break;
	case 23:
#line 98 "hext-machine.rl"
	{ TK_START; }
	break;
	case 24:
#line 98 "hext-machine.rl"
	{ TK_STOP; }
	break;
	case 25:
#line 102 "hext-machine.rl"
	{ pv.regex_flag |= boost::regex::icase; }
	break;
	case 26:
#line 105 "hext-machine.rl"
	{ pv.regex_flag |= boost::regex::collate; }
	break;
	case 27:
#line 107 "hext-machine.rl"
	{ try {
     pv.regex = boost::regex(tok, pv.regex_flag);
   }
   catch( const boost::regex_error& e ) {
     // Mark whole regex as error, including slashes and flags
     auto mark_len = this->p - tok_begin + 2;
     this->throw_regex_error(mark_len, e.code());
   }
}
	break;
	case 28:
#line 117 "hext-machine.rl"
	{ assert(pv.regex); pv.set_test<test::Regex>(*pv.regex); }
	break;
	case 29:
#line 123 "hext-machine.rl"
	{ pv.builtin = GetNodeText; }
	break;
	case 30:
#line 125 "hext-machine.rl"
	{ pv.builtin = GetNodeInnerHtml; }
	break;
	case 31:
#line 127 "hext-machine.rl"
	{ pv.builtin = StripTagsWrapper; }
	break;
	case 32:
#line 136 "hext-machine.rl"
	{ TK_START; }
	break;
	case 33:
#line 137 "hext-machine.rl"
	{ TK_STOP; pv.cap_var = tok; }
	break;
	case 34:
#line 148 "hext-machine.rl"
	{ pv.optional = true; }
	break;
	case 35:
#line 152 "hext-machine.rl"
	{ pv.test = MakeUnique<test::Negate>(std::move(pv.test)); }
	break;
	case 36:
#line 157 "hext-machine.rl"
	{ TK_START; }
	break;
	case 37:
#line 158 "hext-machine.rl"
	{ TK_STOP; pv.attr_name = tok; }
	break;
	case 38:
#line 163 "hext-machine.rl"
	{ TK_START; }
	break;
	case 39:
#line 163 "hext-machine.rl"
	{ TK_STOP; pv.literal_value = tok; }
	break;
	case 40:
#line 170 "hext-machine.rl"
	{ pv.set_test<test::Equals>(pv.literal_value); }
	break;
	case 41:
#line 173 "hext-machine.rl"
	{ pv.set_test<test::BeginsWith>(pv.literal_value); }
	break;
	case 42:
#line 176 "hext-machine.rl"
	{ pv.set_test<test::Contains>(pv.literal_value); }
	break;
	case 43:
#line 179 "hext-machine.rl"
	{ pv.set_test<test::ContainsWord>(pv.literal_value); }
	break;
	case 44:
#line 182 "hext-machine.rl"
	{ pv.set_test<test::EndsWith>(pv.literal_value); }
	break;
	case 45:
#line 190 "hext-machine.rl"
	{ rule.add_capture_pattern<BuiltinCapture>(pv.cap_var, pv.builtin, pv.regex); }
	break;
	case 46:
#line 194 "hext-machine.rl"
	{ rule.add_match_pattern<BuiltinMatch>(pv.builtin, std::move(pv.test)); }
	break;
	case 47:
#line 198 "hext-machine.rl"
	{ rule.add_match_pattern<BuiltinMatch>(pv.builtin, std::move(pv.test)); }
	break;
	case 48:
#line 202 "hext-machine.rl"
	{ rule.add_capture_pattern<AttributeCapture>(pv.cap_var, pv.attr_name, pv.regex);
         if( !pv.optional )
           rule.add_match_pattern<AttributeMatch>(pv.attr_name, MakeUnique<test::True>());
       }
	break;
	case 49:
#line 209 "hext-machine.rl"
	{ rule.add_match_pattern<AttributeMatch>(pv.attr_name, std::move(pv.test)); }
	break;
	case 50:
#line 213 "hext-machine.rl"
	{ rule.add_match_pattern<AttributeMatch>(pv.attr_name, std::move(pv.test)); }
	break;
	case 51:
#line 217 "hext-machine.rl"
	{ pv.set_test<test::True>(); }
	break;
	case 52:
#line 220 "hext-machine.rl"
	{ rule.add_match_pattern<AttributeMatch>(pv.attr_name, std::move(pv.test)); }
	break;
	case 53:
#line 221 "hext-machine.rl"
	{ pv.reset(); }
	break;
	case 54:
#line 241 "hext-machine.rl"
	{ rule.set_optional(true); }
	break;
	case 55:
#line 245 "hext-machine.rl"
	{ TK_START; }
	break;
	case 56:
#line 246 "hext-machine.rl"
	{ TK_STOP;
         auto tag = gumbo_tag_enum(tok.c_str());
         if( tag != GUMBO_TAG_UNKNOWN )
           rule.set_tag(tag);
         else
           this->throw_unknown_token(tok, "html-tag"); }
	break;
	case 57:
#line 264 "hext-machine.rl"
	{ builder.push_rule(std::move(rule), /* self_closing: */ true); }
	break;
	case 58:
#line 266 "hext-machine.rl"
	{ builder.push_rule(std::move(rule), /* self_closing: */ false); }
	break;
	case 59:
#line 267 "hext-machine.rl"
	{ rule = Rule(); }
	break;
	case 60:
#line 280 "hext-machine.rl"
	{ TK_START; }
	break;
	case 61:
#line 281 "hext-machine.rl"
	{ TK_STOP; }
	break;
	case 62:
#line 284 "hext-machine.rl"
	{ if( !builder.pop_closing_tag(tok) )
         this->throw_expected_closing_tag(tok, builder.get_expected_closing_tag()); }
	break;
#line 403 "Parser.cpp.tmp"
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	const char *__acts = _hext_actions + _hext_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 0:
#line 7 "hext-machine.rl"
	{
  this->throw_unexpected();
}
	break;
	case 57:
#line 264 "hext-machine.rl"
	{ builder.push_rule(std::move(rule), /* self_closing: */ true); }
	break;
	case 58:
#line 266 "hext-machine.rl"
	{ builder.push_rule(std::move(rule), /* self_closing: */ false); }
	break;
	case 59:
#line 267 "hext-machine.rl"
	{ rule = Rule(); }
	break;
	case 62:
#line 284 "hext-machine.rl"
	{ if( !builder.pop_closing_tag(tok) )
         this->throw_expected_closing_tag(tok, builder.get_expected_closing_tag()); }
	break;
	case 63:
#line 289 "hext-machine.rl"
	{ {p++; goto _out; } }
	break;
#line 446 "Parser.cpp.tmp"
		}
	}
	}

	_out: {}
	}

#line 54 "Parser.cpp.rl"


  // Throw error if there are missing closing tags.
  if( auto expected_closing_tag = builder.get_expected_closing_tag() )
    this->throw_expected_closing_tag("", expected_closing_tag);

  return builder.take_rule_tree();
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

void Parser::throw_expected_closing_tag(
  const std::string& input,
  boost::optional<GumboTag> expected_closing_tag
) const
{
  if( expected_closing_tag )
  {
    std::string closing_tag_name =
      std::string("</");
    if( *expected_closing_tag != GUMBO_TAG_UNKNOWN )
      closing_tag_name += gumbo_normalized_tagname(*expected_closing_tag);
    closing_tag_name += ">";

    this->throw_error(
      std::string("Expected closing tag '")
      + gumbo_normalized_tagname(*expected_closing_tag)
      + "'",
      input.size() + 3 // strlen("</>")
    );
  }
  else
  {
    std::string closing_tag_name = std::string("</") + input + ">";

    this->throw_error(
      std::string("Unexpected closing tag '")
      + input
      + "'",
      closing_tag_name.size()
    );
  }
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

