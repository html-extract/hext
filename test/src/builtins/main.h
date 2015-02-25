#include "hext/builtins.h"


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

TEST(Builtin_GetNameByBuiltin, Nullptr)
{
  EXPECT_EQ(hext::GetNameByBuiltin(nullptr), "unknown-builtin");
}

TEST(Builtin_GetNameByBuiltin, Unknown)
{
  EXPECT_EQ(hext::GetNameByBuiltin((hext::BuiltinFuncPtr)123), "unknown-builtin");
}

TEST(Builtin_GetNameByBuiltin, Known)
{
  EXPECT_EQ(hext::GetNameByBuiltin(hext::GetNodeText), "text");
  EXPECT_EQ(hext::GetNameByBuiltin(hext::GetNodeInnerHtml), "inner_html");
}


} // namespace

