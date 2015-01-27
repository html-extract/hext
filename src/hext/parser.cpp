#include "hext/parser.h"


namespace hext {
namespace parser {


parse_error::parse_error(const char * msg)
: std::runtime_error(msg)
{
}


state::state()
: indent(0),
  tag_name(),
  is_direct_desc(false),
  cap_limit(0),
  attr_name(),
  cap_var(),
  cap_regex(),
  matchp(),
  capturep()
{
}


std::vector<rule> parse_range(const char * begin, const char * end)
{
  lexer lex(begin, end);
  std::vector<token> tokens = lex.lex();
  std::vector<rule> rules;
  state st;

  for( const auto& tok : tokens )
  {
    // we expect the lexer to have catched all syntax errors
    switch( tok.tid )
    {
      case TK_NEWLINE:
        st.indent = 0;
        break;
      case TK_INDENT:
        st.indent++;
        break;
      case TK_DIRECT_DESC:
        st.is_direct_desc = true;
        break;
      case TK_CAP_LIMIT:
        st.cap_limit = std::stoi(tok.to_string());
        break;
      case TK_TAG_NAME:
        st.tag_name = tok.to_string();
        break;
      case TK_ATTR_NAME:
        st.attr_name = tok.to_string();
        break;
      case TK_CAP_BEGIN:
        break;
      case TK_MATCH_LITERAL:
        {
          std::unique_ptr<match_pattern> p(
            new literal_match(
              st.attr_name, tok.to_string()
            )
          );
          st.matchp.push_back(std::move(p));
        }
        break;
      case TK_MATCH_REGEX:
        {
          std::unique_ptr<match_pattern> p(
            new regex_match(
              st.attr_name, tok.to_string()
            )
          );
          st.matchp.push_back(std::move(p));
        }
        break;
      case TK_CAP_END:
        {
          std::unique_ptr<capture_pattern> p(
            new attribute_capture(
              st.cap_var, st.attr_name, st.cap_regex
            )
          );
          st.capturep.push_back(std::move(p));
          std::unique_ptr<match_pattern> pm(
            new match_pattern(
              st.attr_name
            )
          );
          st.matchp.push_back(std::move(pm));
        }
        break;
      case TK_CAP_VAR:
        st.cap_var = tok.to_string();
        break;
      case TK_CAP_REGEX:
        st.cap_regex = tok.to_string();
        break;
      case TK_RULE_END:
        {
          rule r(
            st.tag_name,
            st.is_direct_desc,
            st.cap_limit,
            std::move(st.matchp),
            std::move(st.capturep)
          );
          // either top-level rule or first rule
          if( st.indent == 0 || rules.empty() )
            rules.push_back(std::move(r));
          else
            rules.back().append_child(std::move(r), st.indent);
          // reset parse state
          st = state();
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

