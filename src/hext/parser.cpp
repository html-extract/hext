#include "hext/parser.h"


namespace hext {
namespace parser {


parse_error::parse_error(const char * msg)
: std::runtime_error(msg)
{
}


std::vector<rule> parse_range(const char * begin, const char * end)
{
  lexer lex(begin, end);
  std::vector<token> tokens = lex.lex();
  std::vector<rule> rules;

  int cur_level = 0;
  attribute cur_attr;
  std::vector<attribute> attrs;
  bool is_direct_desc = false;
  std::string tag_name;

  for( const auto& tok : tokens )
  {
    std::string tok_contents;
    if( tok.tok_begin && tok.tok_end && tok.tok_begin != tok.tok_end )
    {
      assert(tok.tok_begin < tok.tok_end);
      tok_contents.append(tok.tok_begin, tok.tok_end);
    }

    // we expect the lexer to have catched all syntax errors
    // (famous last words)
    switch( tok.tid )
    {
      case TK_INDENT:
        ++cur_level;
        break;
      case TK_DIRECT_DESC:
        is_direct_desc = true;
        break;
      case TK_TAG_NAME:
        tag_name = tok_contents;
        break;
      case TK_ATTR_NAME:
        cur_attr = attribute();
        cur_attr.set_name(tok_contents);
        break;
      case TK_ATTR_LITERAL:
      case TK_ATTR_CAPTURE:
        cur_attr.set_is_capture(tok.tid == TK_ATTR_CAPTURE);
        cur_attr.set_value(tok_contents);
        attrs.push_back(cur_attr);
        break;
      case TK_RULE_END:
        {
          rule r(tag_name, is_direct_desc, std::move(attrs));
          if( cur_level == 0 || rules.empty() )
          {
            rules.push_back(r);
          }
          else
          {
            assert(!rules.empty());
            rules.back().append_child(r, cur_level);
          }
          is_direct_desc = false;
          tag_name = "";
          cur_level = 0;
          attrs.clear();
        }
        break;
      case TK_EOF:
      case TK_RULE_BEGIN:
        break;
      case TK_ERROR:
        throw parse_error("syntax error");
        break;
      default:
        throw parse_error("unknown token");
        break;
    }
  }

  return rules;
}

std::vector<rule> parse_file(const std::string& path)
{
  std::ifstream file;
  // force exception on error
  file.exceptions(std::ios::failbit | std::ios::badbit);
  file.open(path);

  std::string input(
    (std::istreambuf_iterator<char>(file)),
    std::istreambuf_iterator<char>()
  );
  const char * c_begin = input.c_str();
  const char * c_end = c_begin + input.size();

  return parse_range(c_begin, c_end);
}


} // namespace parser
} // namespace hext

