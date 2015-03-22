#include "hext/pattern/LiteralTest.h"


namespace {


TEST(Pattern_LiteralTest, Succeeds)
{
  {
    hext::LiteralTest t("word");
    EXPECT_TRUE(t.test("word"));
  }

  {
    hext::LiteralTest t("");
    EXPECT_TRUE(t.test(""));
  }
}

TEST(Pattern_LiteralTest, Fails)
{
  {
    hext::LiteralTest t("word");
    EXPECT_FALSE(t.test("words"));
    EXPECT_FALSE(t.test("sword"));
    EXPECT_FALSE(t.test("wrd"));
    EXPECT_FALSE(t.test("wor"));
  }

  {
    hext::LiteralTest t("");
    EXPECT_FALSE(t.test("w"));
    EXPECT_FALSE(t.test("word"));
  }
}


} // namespace

