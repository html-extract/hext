#ifndef HEXT_MATCHER_H
#define HEXT_MATCHER_H

#include <cassert>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "gumbo.h"

#include "hext/rule.h"


namespace hext {


class matcher
{
public:
  class match_error : public std::runtime_error
  {
  public:
    match_error(const char * msg)
    : std::runtime_error(msg) {}
  };

  matcher(const char * path)
  : g_outp(nullptr),
    buffer()
  {
    assert(path != nullptr);

    {
      std::ifstream file;
      // force exception on error
      file.exceptions(std::ios::failbit | std::ios::badbit);
      file.open(path);

      std::stringstream stream;
      stream << file.rdbuf();

      this->buffer = stream.str();

      file.close();
    }

    this->g_outp = gumbo_parse(this->buffer.c_str());
    if( this->g_outp == nullptr )
      throw match_error("gumbo_parse returned nullptr");
  }

  void match(rule r) const
  {
    // rough and incomplete sketch:
    // 1. take the top rule from a rule-tree,
    //    try to find matching element by breadth first search in html-tree,
    //    use matching element as new html-tree,
    //    capture any values, if is_capture,
    //    if failed, abandon rule-tree, continue to 1.
    // 2. for each child rule continue to 1.

    // Gumbo notes:
    //   Gumbo html tag to str
    //     const char* gumbo_normalized_tagname(GumboTag tag); 
    //   tag name to gumbo tag
    //     GumboTag gumbo_tag_enum(const char* tagname);
    //   html tag attribute
    //     struct GumboAttribute { .name, .value }
    //     GumboAttribute* 
    //       gumbo_get_attribute(const GumboVector* attrs, const char* name);
    //   element
    //     struct GumboElement { 
    //       .tag (GumboTag), .attributes (GumboVector of GumboAttribute) }
  }

  ~matcher()
  {
    assert(this->g_outp != nullptr);
    gumbo_destroy_output(&kGumboDefaultOptions, this->g_outp);
  }

  matcher(const matcher&) = delete;
  matcher& operator=(const matcher&) = delete;

private:
  GumboOutput * g_outp;
  std::string buffer;
};


} // namespace hext


#endif // HEXT_MATCHER_H

