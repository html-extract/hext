#ifndef HEXT_PARSER_H
#define HEXT_PARSER_H

#include <fstream>
#include <iterator>
#include <string>
#include <exception>

#include "hext/token.h"
#include "hext/lexer.h"
#include "hext/attribute.h"
#include "hext/rule.h"


namespace hext {
namespace parser {


std::vector<rule> 
parse_range(const char * begin, const char * end)
{
  lexer lex(begin, end);
  std::vector<token> tokens = lex.lex();
  std::vector<rule> rules;

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
        std::cout << "TK_ERROR\n";
        throw 1;
        break;
      case TK_INDENT:
        std::cout << "TK_INDENT\n";
        break;
      case TK_RULE_BEGIN:
        std::cout << "TK_RULE_BEGIN\n";
        break;
      case TK_DIRECT_DESC:
        std::cout << "TK_DIRECT_DESC\n";
        break;
      case TK_CAP_LIMIT:
        std::cout << "TK_CAP_LIMIT\n";
        break;
      case TK_TAG_NAME:
        std::cout << "TK_TAG_NAME\n";
        break;
      case TK_ATTR_NAME:
        std::cout << "TK_ATTR_NAME\n";
        break;
      case TK_ATTR_LITERAL:
        std::cout << "TK_ATTR_LITERAL\n";
        break;
      case TK_ATTR_CAPTURE:
        std::cout << "TK_ATTR_CAPTURE\n";
        break;
      case TK_RULE_END:
        std::cout << "TK_RULE_END\n";
        break;
      case TK_EOF:
        std::cout << "TK_EOF\n";
        break;
      default:
        std::cout << "UNKNOWN TAG " << tok.tid << "\n";
        break;
    }

    std::cout << "  contents("
              << tok_contents.size()
              << "): "
              << tok_contents
              << "\n";
  }

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

