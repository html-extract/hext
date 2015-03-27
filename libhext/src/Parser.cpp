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
  // Ragel generates state machines in plain C and knows nothing about
  // namespaces.
  using namespace ragel;
  
#line 27 "Parser.cpp.tmp"
	{
	cs = hext_start;
	}

#line 27 "Parser.cpp.rl"

}

std::vector<Rule> Parser::parse(Option flags)
{
  using namespace ragel;

  // Provide shortcut to keep hext-machine's code smaller.
  typedef NthChildMatch::OffsetOf NthOff;

  // In the hext-machine, rules will be contructed with a RuleBuilder.
  RuleBuilder rule(flags);

  // Same with patterns.
  PatternBuilder& pattern = rule.pattern();

  // These variables will be accessed by the macros TK_START and TK_STOP.
  const char * tok_begin = nullptr;
  const char * tok_end = nullptr;
  std::string tok = "";

  // A flag to tell whether we are currently parsing a rule.
  bool rule_start = false;

  
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
#line 4 "hext-machine.rl"
	{
    this->throw_unexpected();
  }
	break;
	case 1:
#line 8 "hext-machine.rl"
	{
    if( rule_start )
    {
      rule.consume_rule();
      rule_start = false;
    }
    else
    {
      rule.reset_indent();
    }
  }
	break;
	case 2:
#line 39 "hext-machine.rl"
	{
        pattern.set_nth_mul("2");
        pattern.set_nth_add("0");
       }
	break;
	case 3:
#line 47 "hext-machine.rl"
	{
        pattern.set_nth_mul("2");
        pattern.set_nth_add("1");
       }
	break;
	case 4:
#line 56 "hext-machine.rl"
	{ TK_START; }
	break;
	case 5:
#line 57 "hext-machine.rl"
	{ TK_STOP; pattern.set_nth_mul(tok); }
	break;
	case 6:
#line 61 "hext-machine.rl"
	{ // '2n' must behave the same as '2n+0'.
           pattern.set_nth_add("0");
         }
	break;
	case 7:
#line 68 "hext-machine.rl"
	{ TK_START; }
	break;
	case 8:
#line 69 "hext-machine.rl"
	{ TK_STOP; pattern.set_nth_add(tok); }
	break;
	case 9:
#line 81 "hext-machine.rl"
	{ pattern.consume_child_count("0"); }
	break;
	case 10:
#line 89 "hext-machine.rl"
	{ TK_START; }
	break;
	case 11:
#line 90 "hext-machine.rl"
	{ TK_STOP; pattern.consume_child_count(tok); }
	break;
	case 12:
#line 98 "hext-machine.rl"
	{ pattern.consume_nth_child(); }
	break;
	case 13:
#line 103 "hext-machine.rl"
	{
          pattern.consume_nth_child(NthOff::Back);
         }
	break;
	case 14:
#line 110 "hext-machine.rl"
	{
          pattern.consume_nth_child(
            NthOff::Front,
            rule.tag()
          );
         }
	break;
	case 15:
#line 120 "hext-machine.rl"
	{
          pattern.set_nth_mul("1");
          pattern.consume_nth_child();
         }
	break;
	case 16:
#line 128 "hext-machine.rl"
	{
          pattern.set_nth_mul("1");
          pattern.consume_nth_child(
            NthOff::Front,
            rule.tag()
          );
         }
	break;
	case 17:
#line 139 "hext-machine.rl"
	{
          pattern.set_nth_mul("1");
          pattern.consume_nth_child(NthOff::Back);
         }
	break;
	case 18:
#line 147 "hext-machine.rl"
	{
          pattern.set_nth_mul("1");
          pattern.consume_nth_child(
            NthOff::Back,
            rule.tag()
          );
         }
	break;
	case 19:
#line 158 "hext-machine.rl"
	{
          pattern.consume_nth_child(
            NthOff::Back,
            rule.tag()
          );
         }
	break;
	case 20:
#line 168 "hext-machine.rl"
	{
          pattern.set_nth_mul("1");
          pattern.consume_nth_child();
          pattern.set_nth_mul("1");
          pattern.consume_nth_child(NthOff::Back);
         }
	break;
	case 21:
#line 181 "hext-machine.rl"
	{ TK_START; }
	break;
	case 22:
#line 182 "hext-machine.rl"
	{ TK_STOP;
                       pattern.set_attr_literal(tok); }
	break;
	case 23:
#line 197 "hext-machine.rl"
	{ TK_START; }
	break;
	case 24:
#line 198 "hext-machine.rl"
	{ TK_STOP;
                 {
                   if( !pattern.set_builtin(tok) )
                     this->throw_unknown_token(tok, "builtin");
                 }
              }
	break;
	case 25:
#line 208 "hext-machine.rl"
	{ TK_START; }
	break;
	case 26:
#line 209 "hext-machine.rl"
	{ TK_STOP; pattern.set_attr_name(tok); }
	break;
	case 27:
#line 215 "hext-machine.rl"
	{ pattern.set_literal_op(*this->p); }
	break;
	case 28:
#line 225 "hext-machine.rl"
	{ TK_START; }
	break;
	case 29:
#line 226 "hext-machine.rl"
	{ TK_STOP; pattern.set_cap_var(tok); }
	break;
	case 30:
#line 231 "hext-machine.rl"
	{ TK_START; }
	break;
	case 31:
#line 232 "hext-machine.rl"
	{ TK_STOP;
                                 try{ pattern.set_cap_regex(tok); }
                                 catch( const boost::regex_error& e )
                                 { this->throw_regex_error(tok, e.code()); }
                               }
	break;
	case 32:
#line 247 "hext-machine.rl"
	{ TK_START; }
	break;
	case 33:
#line 248 "hext-machine.rl"
	{ TK_STOP;
                                   try{ pattern.set_attr_regex(tok); }
                                   catch( const boost::regex_error& e )
                                   { this->throw_regex_error(tok, e.code()); }
                                 }
	break;
	case 34:
#line 262 "hext-machine.rl"
	{ pattern.consume_pattern(); }
	break;
	case 35:
#line 271 "hext-machine.rl"
	{ rule.increment_indent(); }
	break;
	case 36:
#line 276 "hext-machine.rl"
	{ rule_start = true; }
	break;
	case 37:
#line 281 "hext-machine.rl"
	{
              rule_start = true;
              rule.set_any_descendant(true);
             }
	break;
	case 38:
#line 288 "hext-machine.rl"
	{ rule.set_optional(true); }
	break;
	case 39:
#line 291 "hext-machine.rl"
	{ TK_START; }
	break;
	case 40:
#line 292 "hext-machine.rl"
	{ TK_STOP;
                       if( !rule.set_tag_name(tok) )
                         this->throw_unknown_token(tok, "html-tag"); }
	break;
	case 41:
#line 299 "hext-machine.rl"
	{ rule.set_closed(true); }
	break;
#line 373 "Parser.cpp.tmp"
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
#line 4 "hext-machine.rl"
	{
    this->throw_unexpected();
  }
	break;
	case 1:
#line 8 "hext-machine.rl"
	{
    if( rule_start )
    {
      rule.consume_rule();
      rule_start = false;
    }
    else
    {
      rule.reset_indent();
    }
  }
	break;
	case 9:
#line 81 "hext-machine.rl"
	{ pattern.consume_child_count("0"); }
	break;
	case 12:
#line 98 "hext-machine.rl"
	{ pattern.consume_nth_child(); }
	break;
	case 13:
#line 103 "hext-machine.rl"
	{
          pattern.consume_nth_child(NthOff::Back);
         }
	break;
	case 14:
#line 110 "hext-machine.rl"
	{
          pattern.consume_nth_child(
            NthOff::Front,
            rule.tag()
          );
         }
	break;
	case 15:
#line 120 "hext-machine.rl"
	{
          pattern.set_nth_mul("1");
          pattern.consume_nth_child();
         }
	break;
	case 16:
#line 128 "hext-machine.rl"
	{
          pattern.set_nth_mul("1");
          pattern.consume_nth_child(
            NthOff::Front,
            rule.tag()
          );
         }
	break;
	case 17:
#line 139 "hext-machine.rl"
	{
          pattern.set_nth_mul("1");
          pattern.consume_nth_child(NthOff::Back);
         }
	break;
	case 18:
#line 147 "hext-machine.rl"
	{
          pattern.set_nth_mul("1");
          pattern.consume_nth_child(
            NthOff::Back,
            rule.tag()
          );
         }
	break;
	case 19:
#line 158 "hext-machine.rl"
	{
          pattern.consume_nth_child(
            NthOff::Back,
            rule.tag()
          );
         }
	break;
	case 20:
#line 168 "hext-machine.rl"
	{
          pattern.set_nth_mul("1");
          pattern.consume_nth_child();
          pattern.set_nth_mul("1");
          pattern.consume_nth_child(NthOff::Back);
         }
	break;
	case 24:
#line 198 "hext-machine.rl"
	{ TK_STOP;
                 {
                   if( !pattern.set_builtin(tok) )
                     this->throw_unknown_token(tok, "builtin");
                 }
              }
	break;
	case 26:
#line 209 "hext-machine.rl"
	{ TK_STOP; pattern.set_attr_name(tok); }
	break;
	case 34:
#line 262 "hext-machine.rl"
	{ pattern.consume_pattern(); }
	break;
	case 36:
#line 276 "hext-machine.rl"
	{ rule_start = true; }
	break;
	case 37:
#line 281 "hext-machine.rl"
	{
              rule_start = true;
              rule.set_any_descendant(true);
             }
	break;
	case 38:
#line 288 "hext-machine.rl"
	{ rule.set_optional(true); }
	break;
	case 40:
#line 292 "hext-machine.rl"
	{ TK_STOP;
                       if( !rule.set_tag_name(tok) )
                         this->throw_unknown_token(tok, "html-tag"); }
	break;
	case 41:
#line 299 "hext-machine.rl"
	{ rule.set_closed(true); }
	break;
	case 42:
#line 306 "hext-machine.rl"
	{ {p++; goto _out; } }
	break;
#line 530 "Parser.cpp.tmp"
		}
	}
	}

	_out: {}
	}

#line 52 "Parser.cpp.rl"

  return rule.take_rules();
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
  const std::string& tok,
  boost::regex_constants::error_type e_code
) const
{
  assert(this->p && this->p_begin_ && this->pe);

  std::stringstream error_msg;
  error_msg << "In regular expression ";
  this->print_error_location(tok.size(), error_msg);

  // regex_error::what() not only contains an error message, but also adds the
  // error location. Therefore we use regex_traits::error_string to get a
  // shorter error description.
  boost::regex_traits<boost::regex::value_type> traits;
  error_msg << "\n\nError: "
            << traits.error_string(e_code);

  throw ParseError(error_msg.str());
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

