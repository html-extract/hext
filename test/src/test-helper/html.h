#ifndef TEST_HELPER_HTML_H
#define TEST_HELPER_HTML_H

#include "gtest/gtest.h"

#include <cstring>

#include <gumbo.h>


namespace helper {


class Html
{
public:
  Html(const char * str)
  : g_outp_(
      gumbo_parse_with_options(&kGumboDefaultOptions, str, std::strlen(str))
    )
  {
  }

  ~Html()
  {
    gumbo_destroy_output(&kGumboDefaultOptions, this->g_outp_);
  }

  const GumboNode * root() const
  {
    return this->g_outp_->root;
  }

  const GumboNode * body() const
  {
    const GumboNode * node = this->g_outp_->root;
    if( !node || node->type != GUMBO_NODE_ELEMENT )
      return nullptr;

    const GumboVector& children = node->v.element.children;

    // first child should be <head>, second should be <body> (if they are not
    // present in the input, gumbo will insert them).
    if( children.length < 2 )
      return nullptr;
    node = static_cast<const GumboNode *>(children.data[1]);

    if( !node || node->type != GUMBO_NODE_ELEMENT )
      return nullptr;

    if( node->v.element.tag != GUMBO_TAG_BODY )
      return nullptr;

    return node;
  }

private:
  GumboOutput * g_outp_;
};


} // namespace helper


#endif // TEST_HELPER_HTML_H

