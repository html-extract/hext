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


/// Match nodes that have an attribute href, whose value
/// * is not empty
/// * does not begin with '#'
/// * does not begin with 'javascript:'
class UsefulHrefMatch : public hext::Match
{
public:
  bool matches(const GumboNode * node) const final
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
};


/// Capture the href attribute of a node, store it with name "href".
/// All URIs are passed to Poco::URI, which normalizes and applies
/// a base URI, if given.
class HrefCapture : public hext::Capture
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


/// Return the value of a capture with given name.
boost::optional<std::string>
ResultValueByName(hext::ResultTree * rt, const std::string& name)
{
  assert(rt);
  if( rt == nullptr )
    return {};

  for(const auto& p : rt->values())
    if( p.first == name )
      return p.second;

  for(const auto& child : rt->children())
    if( auto result = ResultValueByName(child.get(), name) )
      return result;

  return {};
}


/// Return the first base tag's href value.
/// Return empty string if no base tag href found.
boost::optional<std::string> BaseUri(const hext::Html& html)
{
  hext::Rule base_href(hext::HtmlTag::BASE);
  base_href
    .add_capture<hext::AttributeCapture>("href", "href");

  auto rt = base_href.extract(html.root());

  return ResultValueByName(rt.get(), "href");
}


/// Slurp the contents of STDIN, extract all href attributes from anchor
/// elements and print them to STDOUT, separated by newline.
/// Exclude empty URIs and URIs that begin with either "javascript:" or "#".
/// If a parameter is passed, it is used as the base-URI for all URIs.
/// If no parameter is passed and there is a <base> element in the document, its
/// href attribute will be used as the base-URI for all URIs.
/// Example usage:
///   curl -sS "http://www.reddit.com" | ./extract-href "http://www.reddit.com/"
int main(int argc, char * argv[])
{
  std::ios_base::sync_with_stdio(false);
  using namespace hext;

  std::stringstream in_sstr;
  {
    std::ifstream in("/dev/stdin");
    in_sstr << in.rdbuf();
  }

  Html html(in_sstr.str());

  std::string base_uri = "";
  if( argc > 1 )
    base_uri = argv[1];
  else if( auto uri = BaseUri(html) )
    base_uri = *uri;

  Rule a_href(HtmlTag::A);
  a_href.add_match<UsefulHrefMatch>()
        .add_capture<HrefCapture>(base_uri);

  auto result_tree = a_href.extract(html.root());
  auto flat_result = result_tree->flatten();

  for(const auto& m : flat_result)
    for(const auto& p : m)
      std::cout << p.second << "\n";

  return EXIT_SUCCESS;
}

