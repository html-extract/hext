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

  int indent = 0;
  std::vector<attribute> attrs;
  bool is_direct_desc = false;
  std::string tag_name;
  std::string attr_name;

  for( const auto& tok : tokens )
  {
    // we expect the lexer to have catched all syntax errors
    // (famous last words)
    switch( tok.tid )
    {
      case TK_INDENT:
        ++indent;
        break;
      case TK_DIRECT_DESC:
        is_direct_desc = true;
        break;
      case TK_TAG_NAME:
        tag_name = tok.to_string();
        break;
      case TK_ATTR_NAME:
        attr_name = tok.to_string();
        break;
      case TK_ATTR_LITERAL:
      case TK_ATTR_CAPTURE:
        {
          attribute attr(
            attr_name,
            tok.to_string(),
            (tok.tid == TK_ATTR_CAPTURE)
          );
          attrs.push_back(attr);
        }
        break;
      case TK_RULE_END:
        {
          rule r(tag_name, is_direct_desc, std::move(attrs));
          if( indent == 0 || rules.empty() )
          {
            rules.push_back(r);
          }
          else
          {
            assert(!rules.empty());
            rules.back().append_child(r, indent);
          }
          is_direct_desc = false;
          attr_name = "";
          tag_name = "";
          indent = 0;
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

