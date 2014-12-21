
#line 1 "/repos/projects/html-extract/src/hext/lexer.cpp.rl"
#include "hext/lexer.h"


namespace hext {


lexer::lex_error::lex_error(const std::string& msg)
: std::runtime_error(msg)
{
}


lexer::lexer(const char * begin, const char * end)
: p_begin(begin),
  p(begin),
  pe(end),
  eof(end),
  cs(0)
{
  using namespace ragel;
  
#line 25 "/repos/projects/html-extract/src/hext/lexer.cpp"
	{
	cs = hext_start;
	}

#line 25 "/repos/projects/html-extract/src/hext/lexer.cpp.rl"

}

std::vector<token> lexer::lex()
{
  using namespace ragel;

  std::vector<token> tokens;

  // this calls throw_error on lexing error
  
#line 42 "/repos/projects/html-extract/src/hext/lexer.cpp"
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
	_trans = _hext_indicies[_trans];
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
#line 4 "/repos/projects/html-extract/src/hext/hext.rl"
	{
    throw_error();
  }
	break;
	case 1:
#line 17 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_START(TK_ATTR_NAME); }
	break;
	case 2:
#line 18 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_STOP; }
	break;
	case 3:
#line 27 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_START(TK_ATTR_CAPTURE); }
	break;
	case 4:
#line 28 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_STOP; }
	break;
	case 5:
#line 34 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_START(TK_ATTR_LITERAL); }
	break;
	case 6:
#line 35 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_STOP; }
	break;
	case 7:
#line 46 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_START(TK_INDENT); }
	break;
	case 8:
#line 47 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_STOP; }
	break;
	case 9:
#line 50 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_START(TK_RULE_BEGIN); }
	break;
	case 10:
#line 51 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_STOP; }
	break;
	case 11:
#line 54 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_START(TK_DIRECT_DESC); }
	break;
	case 12:
#line 55 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_STOP; }
	break;
	case 13:
#line 58 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_START(TK_CAP_LIMIT); }
	break;
	case 14:
#line 59 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_STOP; }
	break;
	case 15:
#line 62 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_START(TK_TAG_NAME); }
	break;
	case 16:
#line 63 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_STOP; }
	break;
	case 17:
#line 67 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_START(TK_RULE_END); }
	break;
	case 18:
#line 68 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_STOP; }
	break;
#line 194 "/repos/projects/html-extract/src/hext/lexer.cpp"
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
#line 4 "/repos/projects/html-extract/src/hext/hext.rl"
	{
    throw_error();
  }
	break;
	case 19:
#line 72 "/repos/projects/html-extract/src/hext/hext.rl"
	{ LX_TK_START(TK_EOF); {p++; goto _out; } }
	break;
#line 220 "/repos/projects/html-extract/src/hext/lexer.cpp"
		}
	}
	}

	_out: {}
	}

#line 36 "/repos/projects/html-extract/src/hext/lexer.cpp.rl"

  return tokens;
}

void lexer::throw_error() const
{
  std::pair<size_t, size_t> pos =
    get_char_position(this->p, this->p_begin, this->pe);

  std::string char_name;
  if( this->p == this->pe )
  {
    char_name = "[eof]";
  }
  else
  {
    if( this->p != nullptr )
      char_name = get_char_name(*this->p);
    else
      char_name = "[unknown]";
  }

  std::stringstream error_msg;
  error_msg << "Error at line "
            << pos.first + 1
            << ", char "
            << pos.second + 1
            << ", unexpected character '"
            << char_name
            << "'";

  throw lex_error(error_msg.str());
}


} // namespace hext

