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

  
#line 52 "Parser.cpp.tmp"
	{
	cs = hext_start;
	}

#line 57 "Parser.cpp.tmp"
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
#line 11 "hext-machine.rl"
	{ pv.nth = {2, 0}; }
	break;
	case 1:
#line 14 "hext-machine.rl"
	{ pv.nth = {2, 1}; }
	break;
	case 2:
#line 18 "hext-machine.rl"
	{ TK_START; }
	break;
	case 3:
#line 19 "hext-machine.rl"
	{ TK_STOP; pv.nth = {0, std::stoi(tok)}; }
	break;
	case 4:
#line 22 "hext-machine.rl"
	{ pv.nth = {pv.nth.second, 0}; }
	break;
	case 5:
#line 24 "hext-machine.rl"
	{ TK_START; }
	break;
	case 6:
#line 25 "hext-machine.rl"
	{ TK_STOP; pv.nth.second = std::stoi(tok); }
	break;
	case 7:
#line 34 "hext-machine.rl"
	{ pv.set_trait<ChildCountMatch>(0); }
	break;
	case 8:
#line 39 "hext-machine.rl"
	{ TK_START; }
	break;
	case 9:
#line 40 "hext-machine.rl"
	{ TK_STOP; pv.set_trait<ChildCountMatch>(std::stoi(tok)); }
	break;
	case 10:
#line 46 "hext-machine.rl"
	{ TK_START; }
	break;
	case 11:
#line 47 "hext-machine.rl"
	{ TK_STOP; pv.set_trait<AttributeCountMatch>(std::stoi(tok)); }
	break;
	case 12:
#line 52 "hext-machine.rl"
	{ pv.set_trait<NthChildMatch>(pv.nth); }
	break;
	case 13:
#line 56 "hext-machine.rl"
	{ pv.set_trait<NthChildMatch>(pv.nth, NthOff::Back); }
	break;
	case 14:
#line 60 "hext-machine.rl"
	{ pv.set_trait<NthChildMatch>(pv.nth, NthOff::Front, rule.get_tag()); }
	break;
	case 15:
#line 64 "hext-machine.rl"
	{ pv.set_trait<NthChildMatch>(0, 1); }
	break;
	case 16:
#line 68 "hext-machine.rl"
	{ pv.set_trait<NthChildMatch>(0, 1, NthOff::Front, rule.get_tag()); }
	break;
	case 17:
#line 72 "hext-machine.rl"
	{ pv.set_trait<NthChildMatch>(0, 1, NthOff::Back); }
	break;
	case 18:
#line 76 "hext-machine.rl"
	{ pv.set_trait<NthChildMatch>(0, 1, NthOff::Back, rule.get_tag()); }
	break;
	case 19:
#line 80 "hext-machine.rl"
	{ pv.set_trait<NthChildMatch>(pv.nth, NthOff::Back, rule.get_tag()); }
	break;
	case 20:
#line 83 "hext-machine.rl"
	{ pv.set_trait<NthChildMatch>(0, 1);
                    pv.set_trait<NthChildMatch>(0, 1, NthOff::Back); }
	break;
	case 21:
#line 87 "hext-machine.rl"
	{ pv.set_trait<TextNodeMatch>(); }
	break;
	case 22:
#line 91 "hext-machine.rl"
	{ pv.negate = MakeUnique<NegateMatch>(); }
	break;
	case 23:
#line 94 "hext-machine.rl"
	{
       assert(pv.negate);
       pv.negate->take_match(std::move(pv.trait));
     }
	break;
	case 24:
#line 104 "hext-machine.rl"
	{ TK_START; }
	break;
	case 25:
#line 104 "hext-machine.rl"
	{ TK_STOP; }
	break;
	case 26:
#line 108 "hext-machine.rl"
	{ pv.regex_flag |= boost::regex::icase; }
	break;
	case 27:
#line 111 "hext-machine.rl"
	{ pv.regex_flag |= boost::regex::collate; }
	break;
	case 28:
#line 113 "hext-machine.rl"
	{ try {
     pv.regex = boost::regex(tok, pv.regex_flag);
   }
   catch( const boost::regex_error& e ) {
     // Mark whole regex as error, including slashes and flags
     auto mark_len = this->p - tok_begin + 1;
     this->throw_regex_error(mark_len, e.code());
   }
}
	break;
	case 29:
#line 123 "hext-machine.rl"
	{ assert(pv.regex); pv.set_test<test::Regex>(*pv.regex); }
	break;
	case 30:
#line 129 "hext-machine.rl"
	{ pv.builtin = NodeText; }
	break;
	case 31:
#line 131 "hext-machine.rl"
	{ pv.builtin = NodeInnerHtml; }
	break;
	case 32:
#line 133 "hext-machine.rl"
	{ pv.builtin = StripTagsWrapper; }
	break;
	case 33:
#line 141 "hext-machine.rl"
	{ TK_START; }
	break;
	case 34:
#line 142 "hext-machine.rl"
	{ TK_STOP; pv.cap_var = tok; }
	break;
	case 35:
#line 153 "hext-machine.rl"
	{ pv.optional = true; }
	break;
	case 36:
#line 157 "hext-machine.rl"
	{ pv.test = MakeUnique<test::Negate>(std::move(pv.test)); }
	break;
	case 37:
#line 162 "hext-machine.rl"
	{ TK_START; }
	break;
	case 38:
#line 163 "hext-machine.rl"
	{ TK_STOP; pv.attr_name = tok; }
	break;
	case 39:
#line 169 "hext-machine.rl"
	{ TK_START; }
	break;
	case 40:
#line 169 "hext-machine.rl"
	{ TK_STOP; pv.literal_value = tok; }
	break;
	case 41:
#line 174 "hext-machine.rl"
	{ TK_START; }
	break;
	case 42:
#line 174 "hext-machine.rl"
	{ TK_STOP; pv.literal_value = tok; }
	break;
	case 43:
#line 181 "hext-machine.rl"
	{ pv.set_test<test::ContainsAllWords>(pv.literal_value); }
	break;
	case 44:
#line 184 "hext-machine.rl"
	{ pv.set_test<test::Equals>(pv.literal_value); }
	break;
	case 45:
#line 187 "hext-machine.rl"
	{ pv.set_test<test::BeginsWith>(pv.literal_value); }
	break;
	case 46:
#line 190 "hext-machine.rl"
	{ pv.set_test<test::Contains>(pv.literal_value); }
	break;
	case 47:
#line 193 "hext-machine.rl"
	{ pv.set_test<test::ContainsWord>(pv.literal_value); }
	break;
	case 48:
#line 196 "hext-machine.rl"
	{ pv.set_test<test::EndsWith>(pv.literal_value); }
	break;
	case 49:
#line 204 "hext-machine.rl"
	{ rule.add_capture<BuiltinCapture>(pv.cap_var, pv.builtin, pv.regex); }
	break;
	case 50:
#line 208 "hext-machine.rl"
	{ rule.add_match<BuiltinMatch>(pv.builtin, std::move(pv.test)); }
	break;
	case 51:
#line 212 "hext-machine.rl"
	{ rule.add_match<BuiltinMatch>(pv.builtin, std::move(pv.test)); }
	break;
	case 52:
#line 216 "hext-machine.rl"
	{ rule.add_capture<AttributeCapture>(pv.cap_var, pv.attr_name, pv.regex);
         if( !pv.optional )
           rule.add_match<AttributeMatch>(pv.attr_name, MakeUnique<test::NotNull>());
       }
	break;
	case 53:
#line 223 "hext-machine.rl"
	{ rule.add_match<AttributeMatch>(pv.attr_name, std::move(pv.test)); }
	break;
	case 54:
#line 227 "hext-machine.rl"
	{ rule.add_match<AttributeMatch>(pv.attr_name, std::move(pv.test)); }
	break;
	case 55:
#line 231 "hext-machine.rl"
	{ pv.set_test<test::NotNull>(); }
	break;
	case 56:
#line 234 "hext-machine.rl"
	{ rule.add_match<AttributeMatch>(pv.attr_name, std::move(pv.test)); }
	break;
	case 57:
#line 235 "hext-machine.rl"
	{ pv.reset(); }
	break;
	case 58:
#line 256 "hext-machine.rl"
	{ rule.set_optional(true); }
	break;
	case 59:
#line 260 "hext-machine.rl"
	{ rule.set_tag(GUMBO_TAG_UNKNOWN); }
	break;
	case 60:
#line 265 "hext-machine.rl"
	{ TK_START; }
	break;
	case 61:
#line 266 "hext-machine.rl"
	{ TK_STOP;
           auto tag = gumbo_tag_enum(tok.c_str());
           if( tag != GUMBO_TAG_UNKNOWN )
             rule.set_tag(tag);
           else
             this->throw_invalid_tag(tok); }
	break;
	case 62:
#line 277 "hext-machine.rl"
	{ rule.take_match(std::move(pv.negate)); }
	break;
	case 63:
#line 280 "hext-machine.rl"
	{ rule.take_match(std::move(pv.trait)); }
	break;
	case 64:
#line 290 "hext-machine.rl"
	{ builder.push_rule(std::move(rule), /* self_closing: */ true); }
	break;
	case 65:
#line 292 "hext-machine.rl"
	{ builder.push_rule(std::move(rule), /* self_closing: */ false); }
	break;
	case 66:
#line 293 "hext-machine.rl"
	{ rule = Rule(); }
	break;
	case 67:
#line 302 "hext-machine.rl"
	{ TK_START; }
	break;
	case 68:
#line 303 "hext-machine.rl"
	{ TK_STOP;
         if( !builder.pop_tag(tok) )
           this->throw_unexpected_tag(tok, builder.get_expected_tag()); }
	break;
	case 69:
#line 309 "hext-machine.rl"
	{ this->throw_unexpected(); }
	break;
#line 432 "Parser.cpp.tmp"
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
	case 64:
#line 290 "hext-machine.rl"
	{ builder.push_rule(std::move(rule), /* self_closing: */ true); }
	break;
	case 65:
#line 292 "hext-machine.rl"
	{ builder.push_rule(std::move(rule), /* self_closing: */ false); }
	break;
	case 66:
#line 293 "hext-machine.rl"
	{ rule = Rule(); }
	break;
	case 69:
#line 309 "hext-machine.rl"
	{ this->throw_unexpected(); }
	break;
#line 464 "Parser.cpp.tmp"
		}
	}
	}

	_out: {}
	}

#line 53 "Parser.cpp.rl"


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

