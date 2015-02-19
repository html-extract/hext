#include "hext/parser.h"


namespace hext {
namespace parser {


parse_error::parse_error(const std::string& msg)
: std::runtime_error(msg)
{
}

std::vector<rule> parse_range(const char * begin, const char * end)
{
  lexer lex(begin, end);
  std::vector<token> tokens = lex.lex();
  rule_builder builder;
  bool rule_start = false;

  for( const auto& tok : tokens )
  {
    // we expect the lexer to have catched all syntax errors
    switch( tok.tid )
    {
      case TK_NEWLINE:
      case TK_EOF:
        if( rule_start )
        {
          builder.consume_and_reset();
          rule_start = false;
        }
        builder.reset_indent();
        break;
      case TK_INDENT:
        builder.increment_indent();
        break;
      case TK_DIRECT_DESC:
        builder.set_direct_descendant(true);
        break;
      case TK_NTH_CHILD:
        builder.set_nth_child(std::stoi(tok.to_string()));
        break;
      case TK_TAG_NAME:
        builder.set_tag_name(tok.to_string());
        break;
      case TK_BUILTIN_NAME:
      {
        bi::builtin_func_ptr bf = bi::get_builtin_by_name(tok.to_string());
        if( !bf )
          throw parse_error("Unknown builtin '" + tok.to_string() + "'");
        builder.pattern().set_builtin_function(bf);
        break;
      }
      case TK_ATTR_NAME:
        builder.pattern().set_attr_name(tok.to_string());
        break;
      case TK_MATCH_LITERAL:
        builder.pattern().set_attr_literal(tok.to_string());
        builder.consume_match_pattern();
        break;
      case TK_MATCH_REGEX:
        builder.pattern().set_attr_regex(tok.to_string());
        builder.consume_match_pattern();
        break;
      case TK_CAP_END:
        builder.consume_capture_pattern();
        break;
      case TK_CAP_VAR:
        builder.pattern().set_cap_var(tok.to_string());
        break;
      case TK_CAP_REGEX:
        builder.pattern().set_cap_regex(tok.to_string());
        break;
      case TK_RULE_END:
        builder.set_closed(true);
        break;
      case TK_RULE_BEGIN:
        rule_start = true;
        break;
      case TK_ERROR:
        throw parse_error("syntax error");
      default:
        throw parse_error("unknown token");
    }
  }

  return builder.get_rules_and_reset();
}


} // namespace parser
} // namespace hext

