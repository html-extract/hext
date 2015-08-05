#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

#include <Poco/URI.h>
#include <boost/optional.hpp>

#include "hext/Hext.h"

#include <gumbo.h>


namespace {


/// Captures the href attribute of a node, store it with name "href".
/// All URIs are passed to Poco::URI, which normalizes and applies
/// a base URI, if given.
class HrefCapture : public hext::Cloneable<HrefCapture, hext::Capture>
{
public:
  explicit HrefCapture(const std::string& base_uri = "")
  : base_uri_(base_uri)
  {
  }

  boost::optional<hext::ResultPair> capture(const GumboNode * node) const final
  {
    if( !node || node->type != GUMBO_NODE_ELEMENT )
      return {};

    const GumboAttribute * g_attr = gumbo_get_attribute(
      &node->v.element.attributes,
      "href"
    );

    if( !g_attr || !g_attr->value )
      return {};

    Poco::URI uri(this->base_uri_, g_attr->value);
    return hext::ResultPair("href", uri.toString());
  }

private:
  Poco::URI base_uri_;
};


/// Returns true for nodes that have an attribute href, whose value
/// * is not empty
/// * does not begin with '#'
/// * does not begin with 'javascript:'
bool has_useful_href(const GumboNode * node)
{
  if( !node || node->type != GUMBO_NODE_ELEMENT )
    return false;

  const GumboAttribute * g_attr = gumbo_get_attribute(
    &node->v.element.attributes,
    "href"
  );

  if( !g_attr || !g_attr->value )
    return false;

  std::string str_subj = g_attr->value;
  if( str_subj.empty() || str_subj[0] == '#' )
    return false;

  const char * prefix = "javascript:";
  std::size_t len = std::strlen(prefix);

  if( str_subj.size() < len )
    return true;

  return str_subj.compare(0, len, prefix) != 0;
}


/// Returns the first base tag's href value.
/// Returns empty string if no base tag href found.
boost::optional<std::string> BaseUri(const hext::Html& html)
{
  hext::Rule base_href(hext::HtmlTag::BASE,
                       /* optional: */ false,
                       /* any_descendant: */ true);

  base_href
    .append_capture<hext::AttributeCapture>("href", "href");

  auto result = base_href.extract(html.root());

  if( result.empty() )
    return {};

  if( result.front().count("href") )
    return result.front().find("href")->second;

  return {};
}


} // namespace


/// Slurps the contents of STDIN, extracts all href attributes from anchor
/// elements and prints them to STDOUT, separated by newline.
/// Excludes empty URIs and URIs that begin with either "javascript:" or "#".
/// If a parameter is passed, it is used as the base-URI for all URIs.
/// If no parameter is passed and there is a <base> element in the document, its
/// href attribute will be used as the base-URI for all URIs.
/// Example usage:
///   curl -sS "http://www.reddit.com" | ./extract-href "http://www.reddit.com/"
int main(int argc, char * argv[])
{
  using namespace hext;

  std::ios_base::sync_with_stdio(false);

  std::stringstream in_sstr;
  {
    std::ifstream in("/dev/stdin");
    in_sstr << in.rdbuf();
  }

  auto str = in_sstr.str();
  Html html(str.c_str(), str.size());

  std::string base_uri = "";
  if( argc > 1 )
    base_uri = argv[1];
  else if( auto uri = BaseUri(html) )
    base_uri = *uri;

  Rule body(HtmlTag::BODY);
  body.set_any_descendant(true)
      .append_child(Rule(HtmlTag::A)
                      .set_any_descendant(true)
                      .append_match<FunctionMatch>(has_useful_href)
                      .append_capture<HrefCapture>(base_uri));

  auto result = body.extract(html.root());

  for(const auto& m : result)
    for(const auto& p : m)
      std::cout << p.second << "\n";

  return EXIT_SUCCESS;
}

