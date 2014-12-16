#ifndef HEXT_PARSER_H
#define HEXT_PARSER_H

#include <cassert>
#include <fstream>
#include <iterator>
#include <string>
#include <stdexcept>

#include "hext/token.h"
#include "hext/lexer.h"
#include "hext/attribute.h"
#include "hext/rule.h"


namespace hext {
namespace parser {


class parse_error : public std::runtime_error
{
public:
  parse_error(const char * msg)
  : std::runtime_error(msg) {}
};


void append_rule(
  std::vector<rule>::iterator begin,
  std::vector<rule>::iterator end,
  rule r,
  int level
)
{
  assert(begin != end);
  std::vector<rule>::iterator it(end - 1);

  if( level > 1 && it->children_size() )
  {
    append_rule(it->children_begin(), it->children_end(), r, level - 1);
    return;
  }

  it->append_child(r);
}

std::vector<rule> 
parse_range(const char * begin, const char * end)
{
  lexer lex(begin, end);
  std::vector<token> tokens = lex.lex();
  std::vector<rule> rules;
  rule cur_rule;
  attribute cur_attr;
  int cur_level = 0;

  for( const auto& tok : tokens )
  {
    std::string tok_contents;
    if( 
      tok.tok_begin != nullptr &&
      tok.tok_end   != nullptr &&
      tok.tok_begin != tok.tok_end
    )
    {
      assert(tok.tok_begin < tok.tok_end);
      tok_contents.append(tok.tok_begin, tok.tok_end);
    }

    // we expect the lexer to have catched all syntax errors
    // (famous last words)
    switch( tok.tid )
    {
      case TK_ERROR:
        std::cout << "TK_ERROR ";
        throw parse_error("syntax error");
        break;
      case TK_INDENT:
        std::cout << "TK_INDENT ";
        ++cur_level;
        break;
      case TK_RULE_BEGIN:
        std::cout << "TK_RULE_BEGIN ";
        break;
      case TK_DIRECT_DESC:
        std::cout << "TK_DIRECT_DESC ";
        cur_rule.set_is_direct_descendant(true);
        break;
      case TK_CAP_LIMIT:
        std::cout << "TK_CAP_LIMIT ";
        if( tok_contents == "*" )
          cur_rule.set_capture_limit(0);
        else
          cur_rule.set_capture_limit(std::stoi(tok_contents));
        break;
      case TK_TAG_NAME:
        std::cout << "TK_TAG_NAME ";
        cur_rule.set_tag_name(tok_contents);
        break;
      case TK_ATTR_NAME:
        std::cout << "TK_ATTR_NAME ";
        cur_attr = attribute();
        cur_attr.set_name(tok_contents);
        break;
      case TK_ATTR_LITERAL:
        std::cout << "TK_ATTR_LITERAL ";
        cur_attr.set_is_capture(false);
        cur_attr.set_value(tok_contents);
        cur_rule.append_attribute(cur_attr);
        break;
      case TK_ATTR_CAPTURE:
        std::cout << "TK_ATTR_CAPTURE ";
        cur_attr.set_is_capture(true);
        cur_attr.set_value(tok_contents);
        cur_rule.append_attribute(cur_attr);
        break;
      case TK_RULE_END:
        std::cout << "TK_RULE_END ";
        if( cur_level == 0 || rules.empty() )
        {
          rules.push_back(cur_rule);
        }
        else
        {
          append_rule(rules.begin(), rules.end(), cur_rule, cur_level);
        }
        cur_rule = rule();
        cur_level = 0;
        break;
      case TK_EOF:
        std::cout << "TK_EOF ";
        break;
      default:
        std::cout << "UNKNOWN TAG " << (int)tok.tid << " ";
        break;
    }

  }
  
  std::cout << "\n";

  return rules;
}


std::vector<rule>
parse_file(const char * path)
{
  std::ifstream in;
  in.open(path);

  std::string input(
    (std::istreambuf_iterator<char>(in)),
    std::istreambuf_iterator<char>()
  );
  const char * c_begin = input.c_str();
  const char * c_end = c_begin + input.size();

  return parse_range(c_begin, c_end);
}


} // namespace parser
} // namespace hext


#endif // HEXT_PARSER_H

