
#line 1 "hext/lexer.rl"
#ifndef HEXT_LEXER_H
#define HEXT_LEXER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>

#include "hext/token.h"

#define LX_TK_START(tk_id) \
  token tok;               \
  tok.tid = tk_id;         \
  tok.tok_begin = p;       \
  tok.tok_end = nullptr;   \
  tokens.push_back(tok);

#define LX_TK_STOP                          \
  assert(tokens.size() > 0);                \
  tokens.at(tokens.size() - 1).tok_end = p;

namespace hext {


namespace ragel {
  
#line 30 "hext/lexer.h"
static const char _hext_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 9, 1, 10, 1, 12, 1, 
	14, 1, 16, 1, 17, 1, 18, 1, 
	19, 2, 0, 19, 2, 2, 17, 2, 
	3, 4, 2, 5, 6, 2, 8, 7, 
	2, 8, 9, 2, 10, 11, 2, 10, 
	13, 2, 10, 15, 2, 10, 17, 2, 
	12, 13, 2, 12, 15, 2, 12, 17, 
	2, 14, 15, 2, 14, 17, 2, 16, 
	17
};

static const char _hext_key_offsets[] = {
	0, 0, 1, 3, 15, 22, 35, 36, 
	42, 46, 47, 48, 53, 54, 63, 72, 
	83, 91, 103, 113
};

static const char _hext_trans_keys[] = {
	32, 32, 60, 32, 33, 42, 62, 9, 
	13, 49, 57, 65, 90, 97, 122, 32, 
	9, 13, 65, 90, 97, 122, 32, 45, 
	61, 62, 95, 9, 13, 48, 57, 65, 
	90, 97, 122, 34, 34, 40, 65, 90, 
	97, 122, 32, 62, 9, 13, 10, 58, 
	41, 65, 90, 97, 122, 34, 41, 45, 
	95, 48, 57, 65, 90, 97, 122, 34, 
	45, 95, 48, 57, 65, 90, 97, 122, 
	32, 42, 62, 9, 13, 49, 57, 65, 
	90, 97, 122, 32, 62, 9, 13, 65, 
	90, 97, 122, 32, 45, 62, 95, 9, 
	13, 48, 57, 65, 90, 97, 122, 32, 
	62, 9, 13, 48, 57, 65, 90, 97, 
	122, 32, 60, 0
};

static const char _hext_single_lengths[] = {
	0, 1, 2, 4, 1, 5, 1, 2, 
	2, 1, 1, 1, 1, 3, 3, 3, 
	2, 4, 2, 2
};

static const char _hext_range_lengths[] = {
	0, 0, 0, 4, 3, 4, 0, 2, 
	1, 0, 0, 2, 0, 3, 3, 4, 
	3, 4, 4, 0
};

static const char _hext_index_offsets[] = {
	0, 0, 2, 5, 14, 19, 29, 31, 
	36, 40, 42, 44, 48, 50, 57, 64, 
	72, 78, 87, 94
};

static const char _hext_indicies[] = {
	1, 0, 2, 3, 0, 4, 5, 6, 
	8, 4, 7, 9, 9, 0, 10, 10, 
	11, 11, 0, 12, 13, 14, 15, 13, 
	12, 13, 13, 13, 0, 16, 0, 17, 
	18, 19, 19, 0, 10, 20, 10, 0, 
	21, 0, 22, 0, 23, 24, 24, 0, 
	25, 0, 26, 27, 27, 27, 27, 27, 
	0, 28, 29, 29, 29, 29, 29, 0, 
	30, 31, 33, 30, 32, 34, 34, 0, 
	35, 36, 35, 37, 37, 0, 38, 39, 
	40, 39, 38, 39, 39, 39, 0, 35, 
	36, 35, 41, 37, 37, 0, 42, 43, 
	0, 0
};

static const char _hext_trans_targs[] = {
	0, 2, 1, 3, 4, 15, 16, 18, 
	9, 17, 4, 5, 4, 5, 6, 9, 
	7, 8, 10, 14, 9, 19, 11, 12, 
	13, 8, 12, 13, 8, 14, 4, 16, 
	18, 9, 17, 4, 9, 17, 4, 17, 
	9, 18, 1, 3
};

static const char _hext_trans_actions[] = {
	1, 0, 45, 48, 19, 51, 54, 54, 
	60, 57, 0, 3, 5, 0, 5, 36, 
	0, 42, 0, 11, 27, 29, 0, 39, 
	7, 0, 9, 0, 13, 0, 21, 63, 
	63, 69, 66, 23, 75, 72, 25, 0, 
	78, 0, 15, 17
};

static const char _hext_eof_actions[] = {
	0, 33, 33, 33, 33, 33, 33, 33, 
	33, 33, 33, 33, 33, 33, 33, 33, 
	33, 33, 33, 31
};

static const int hext_start = 19;
static const int hext_first_final = 19;
static const int hext_error = 0;

static const int hext_en_main = 19;


#line 30 "hext/lexer.rl"

}


class lexer
{
public:
  lexer(const char * begin, const char * end)
  : p_begin(begin),
    p(begin),
    pe(end),
    eof(end),
    cs(0)
  {
    using namespace ragel;
    
#line 151 "hext/lexer.h"
	{
	cs = hext_start;
	}

#line 46 "hext/lexer.rl"
  }

  std::vector<token> lex()
  {
    using namespace ragel;

    std::vector<token> tokens;

    // this throws on lexing error
    
#line 167 "hext/lexer.h"
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
#line 4 "hext/hext.rl"
	{
    print_error();
    {p++; goto _out; }
  }
	break;
	case 1:
#line 18 "hext/hext.rl"
	{ LX_TK_START(TK_ATTR_NAME); }
	break;
	case 2:
#line 19 "hext/hext.rl"
	{ LX_TK_STOP; }
	break;
	case 3:
#line 28 "hext/hext.rl"
	{ LX_TK_START(TK_ATTR_CAPTURE); }
	break;
	case 4:
#line 29 "hext/hext.rl"
	{ LX_TK_STOP; }
	break;
	case 5:
#line 35 "hext/hext.rl"
	{ LX_TK_START(TK_ATTR_LITERAL); }
	break;
	case 6:
#line 36 "hext/hext.rl"
	{ LX_TK_STOP; }
	break;
	case 7:
#line 47 "hext/hext.rl"
	{ LX_TK_START(TK_INDENT); }
	break;
	case 8:
#line 48 "hext/hext.rl"
	{ LX_TK_STOP; }
	break;
	case 9:
#line 51 "hext/hext.rl"
	{ LX_TK_START(TK_RULE_BEGIN); }
	break;
	case 10:
#line 52 "hext/hext.rl"
	{ LX_TK_STOP; }
	break;
	case 11:
#line 55 "hext/hext.rl"
	{ LX_TK_START(TK_DIRECT_DESC); }
	break;
	case 12:
#line 56 "hext/hext.rl"
	{ LX_TK_STOP; }
	break;
	case 13:
#line 59 "hext/hext.rl"
	{ LX_TK_START(TK_CAP_LIMIT); }
	break;
	case 14:
#line 60 "hext/hext.rl"
	{ LX_TK_STOP; }
	break;
	case 15:
#line 63 "hext/hext.rl"
	{ LX_TK_START(TK_TAG_NAME); }
	break;
	case 16:
#line 64 "hext/hext.rl"
	{ LX_TK_STOP; }
	break;
	case 17:
#line 68 "hext/hext.rl"
	{ LX_TK_START(TK_RULE_END); }
	break;
	case 18:
#line 69 "hext/hext.rl"
	{ LX_TK_STOP; }
	break;
#line 320 "hext/lexer.h"
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
#line 4 "hext/hext.rl"
	{
    print_error();
    {p++; goto _out; }
  }
	break;
	case 19:
#line 73 "hext/hext.rl"
	{ LX_TK_START(TK_EOF); {p++; goto _out; } }
	break;
#line 347 "hext/lexer.h"
		}
	}
	}

	_out: {}
	}

#line 56 "hext/lexer.rl"

    return tokens;
  }

  void print_error()
  {
    std::string all_to_error(this->p_begin, this->p);
    int line_nr = 
      std::count(all_to_error.begin(), all_to_error.end(), '\n');

    size_t char_nr = 0;
    size_t line_offset = 0;
    if( line_nr )
    {
      line_offset = all_to_error.find_last_of('\n');
      if( line_offset == std::string::npos )
        line_offset = 1;
      // move past \n
      line_offset += 1;
    }
    char_nr = std::distance(this->p_begin, this->p) - line_offset;

    std::string error_token;
    if( *p == '\n' )
      error_token = "[newline]";
    else if( *p == ' ' )
      error_token = "[space]";
    else 
      error_token = *p;

    std::cerr << "Error at line "
              << line_nr + 1
              << ", char "
              << char_nr + 1
              << ", unexpected character '"
              << error_token
              << "'\n";
  }

private:
  const char * p_begin;
  const char * p;
  const char * pe;
  const char * eof;
  int cs;
};


} // namespace hext


#endif // HEXT_LEXER_H

