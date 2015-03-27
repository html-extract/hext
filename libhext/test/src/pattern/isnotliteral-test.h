#include "hext/pattern/IsNotLiteralTest.h"


namespace {


TEST(Pattern_IsNotLiteralTest, Succeeds)
{
  {
    hext::IsNotLiteralTest t("word");
    EXPECT_TRUE(t.test("sword"));
    EXPECT_TRUE(t.test("swords"));
    EXPECT_TRUE(t.test("words"));
    EXPECT_TRUE(t.test("nope"));
  }
}

TEST(Pattern_IsNotLiteralTest, Fails)
{
  {
    hext::IsNotLiteralTest t("word");
    EXPECT_FALSE(t.test("word"));
  }

  {
    hext::IsNotLiteralTest t("");
    EXPECT_FALSE(t.test(""));
  }
}


} // namespace

