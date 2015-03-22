#ifndef TEST_HELPER_NODE_H
#define TEST_HELPER_NODE_H

#include "gtest/gtest.h"

#include <cassert>
#include <string>

#include <gumbo.h>


namespace helper {


GumboTag tag(const GumboNode * node)
{
  EXPECT_NE(node, nullptr);
  EXPECT_EQ(node->type, GUMBO_NODE_ELEMENT);

  return node->v.element.tag;
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


} // namespace helper


#endif // TEST_HELPER_NODE_H

