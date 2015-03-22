#ifndef TEST_HELPER_HTML_H
#define TEST_HELPER_HTML_H

#include "gtest/gtest.h"

#include <cstring>

#include <gumbo.h>


namespace helper {


class Html
{
public:
  explicit Html(const char * str)
  : g_outp_(
      gumbo_parse_with_options(&kGumboDefaultOptions, str, std::strlen(str))
    )
  {
  }

  ~Html()
  {
    if( this->g_outp_)
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
    {
      std::cerr << "helper::Html:" << __LINE__ << ": gumbo returned null\n";
      return nullptr;
    }

    const GumboVector& children = node->v.element.children;

    // first child should be <head>, second should be <body> (if they are not
    // present in the input, gumbo will insert them).
    if( children.length < 2 )
    {
      std::cerr << "helper::Html:" << __LINE__ << ": children.length < 2\n";
      return nullptr;
    }
    node = static_cast<const GumboNode *>(children.data[1]);

    if( !node || node->type != GUMBO_NODE_ELEMENT )
    {
      std::cerr << "helper::Html:" << __LINE__
                << ": expected body is not a GUMBO_NODE_ELEMENT\n";
      return nullptr;
    }

    if( node->v.element.tag != GUMBO_TAG_BODY )
    {
      std::cerr << "helper::Html:" << __LINE__
                << ": expected body not having tag GUMBO_TAG_BODY\n";
      return nullptr;
    }

    return node;
  }

private:
  Html(const Html&) = delete;
  Html& operator=(const Html&) = delete;

  GumboOutput * g_outp_;
};


} // namespace helper


#endif // TEST_HELPER_HTML_H

