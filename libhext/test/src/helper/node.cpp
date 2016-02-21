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

#include "helper/node.h"


hext::HtmlTag tag(const GumboNode * node)
{
  EXPECT_NE(node, nullptr);
  EXPECT_EQ(node->type, GUMBO_NODE_ELEMENT);

  return static_cast<hext::HtmlTag>(node->v.element.tag);
}

std::string attr_value(const GumboNode * node, const char * attr_name)
{
  EXPECT_NE(node, nullptr);
  EXPECT_NE(attr_name, nullptr);
  EXPECT_EQ(node->type, GUMBO_NODE_ELEMENT);

  const GumboAttribute * g_attr = gumbo_get_attribute(
    &node->v.element.attributes,
    attr_name
  );

  EXPECT_NE(g_attr, nullptr);
  EXPECT_NE(g_attr->value, nullptr);

  return std::string(g_attr->value);
}

