#include "hext/pattern/EndsWithTest.h"


namespace {


TEST(Pattern_EndsWithTest, Succeeds)
{
  {
    hext::EndsWithTest t("word");
    EXPECT_TRUE(t.test("word"));
    EXPECT_TRUE(t.test("sword"));
    EXPECT_TRUE(t.test(" word"));
    EXPECT_TRUE(t.test("wordwordword"));
    EXPECT_TRUE(t.test("word word word"));
  }
}

TEST(Pattern_EndsWithTest, Fails)
{
  {
    hext::EndsWithTest t("word");
    EXPECT_FALSE(t.test("words"));
    EXPECT_FALSE(t.test("swor"));
    EXPECT_FALSE(t.test("wrd"));
    EXPECT_FALSE(t.test("wordwor"));
  }
}


} // namespace

