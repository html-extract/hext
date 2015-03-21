#include "hext/Builtins.h"


namespace {


TEST(Builtin_GetBuiltinByName, Empty)
{
  EXPECT_EQ(hext::GetBuiltinByName(""), nullptr);
}

TEST(Builtin_GetBuiltinByName, Unknown)
{
  EXPECT_EQ(hext::GetBuiltinByName("unknown"), nullptr);
}

TEST(Builtin_GetBuiltinByName, Known)
{
  EXPECT_TRUE(hext::GetBuiltinByName("text") == hext::GetNodeText);
  EXPECT_TRUE(hext::GetBuiltinByName("inner_html") == hext::GetNodeInnerHtml);
}


} // namespace

