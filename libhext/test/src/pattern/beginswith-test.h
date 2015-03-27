#include "hext/pattern/BeginsWithTest.h"


namespace {


TEST(Pattern_BeginsWithTest, Succeeds)
{
  {
    hext::BeginsWithTest t("word");
    EXPECT_TRUE(t.test("word"));
    EXPECT_TRUE(t.test("words"));
    EXPECT_TRUE(t.test("word s"));
  }

  {
    hext::BeginsWithTest t(" ");
    EXPECT_TRUE(t.test(" "));
    EXPECT_TRUE(t.test(" word"));
  }
}

TEST(Pattern_BeginsWithTest, Fails)
{
  {
    hext::BeginsWithTest t("word");
    EXPECT_FALSE(t.test("swords"));
    EXPECT_FALSE(t.test("sword"));
    EXPECT_FALSE(t.test("wrd"));
    EXPECT_FALSE(t.test("wor"));
    EXPECT_FALSE(t.test("w"));
  }
}


} // namespace

