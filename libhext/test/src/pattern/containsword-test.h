#include "hext/pattern/ContainsWordTest.h"


namespace {


TEST(Pattern_ContainsWordTest, Succeeds)
{
  {
    hext::ContainsWordTest t("word");
    EXPECT_TRUE(t.test("word"));
    EXPECT_TRUE(t.test("word "));
    EXPECT_TRUE(t.test("word a"));
    EXPECT_TRUE(t.test("sword word a"));
    EXPECT_TRUE(t.test(" word"));
    EXPECT_TRUE(t.test("a word"));
  }
}

TEST(Pattern_ContainsWordTest, Fails)
{
  {
    hext::ContainsWordTest t("word");
    EXPECT_FALSE(t.test("words"));
    EXPECT_FALSE(t.test("sword"));
    EXPECT_FALSE(t.test("swords"));
    EXPECT_FALSE(t.test("swordsword"));
    EXPECT_FALSE(t.test("wrd"));
    EXPECT_FALSE(t.test("wor"));
  }

  {
    hext::ContainsWordTest t("");
    EXPECT_FALSE(t.test("w"));
    EXPECT_FALSE(t.test("word"));
  }
}


} // namespace

