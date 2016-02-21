// Copyright 2015 Thomas Trapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TEST_HELPER_HTML_H
#define TEST_HELPER_HTML_H

#include "gtest/gtest.h"

#include <cstring>

#include <gumbo.h>


class THtml
{
public:
  explicit THtml(const char * str)
  : g_outp_(
      gumbo_parse_with_options(&kGumboDefaultOptions, str, std::strlen(str))
    )
  {
  }

  ~THtml()
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
      std::cerr << "THtml:" << __LINE__ << ": gumbo returned null\n";
      return nullptr;
    }

    const GumboVector& children = node->v.element.children;

    // first child should be <head>, second should be <body> (if they are not
    // present in the input, gumbo will insert them).
    if( children.length < 2 )
    {
      std::cerr << "THtml:" << __LINE__ << ": children.length < 2\n";
      return nullptr;
    }
    node = static_cast<const GumboNode *>(children.data[1]);

    if( !node || node->type != GUMBO_NODE_ELEMENT )
    {
      std::cerr << "THtml:" << __LINE__
                << ": expected body is not a GUMBO_NODE_ELEMENT\n";
      return nullptr;
    }

    if( node->v.element.tag != GUMBO_TAG_BODY )
    {
      std::cerr << "THtml:" << __LINE__
                << ": expected body not having tag GUMBO_TAG_BODY\n";
      return nullptr;
    }

    return node;
  }

  const GumboNode * body_child(unsigned int pos = 0) const
  {
    auto body_node = this->body();
    if( !body_node || body_node->type != GUMBO_NODE_ELEMENT )
      // an error was already printed
      return nullptr;

    const GumboVector& children = body_node->v.element.children;
    if( pos && pos <= children.length )
      return static_cast<const GumboNode *>(children.data[pos - 1]);

    std::cerr << "THtml:" << __LINE__
              << ": no child in body at position " << pos << "\n";
    return nullptr;
  }

  const GumboNode * first() const
  {
    return this->body_child(1);
  }

private:
  THtml(const THtml&) = delete;
  THtml& operator=(const THtml&) = delete;

  GumboOutput * g_outp_;
};


#endif // TEST_HELPER_HTML_H

