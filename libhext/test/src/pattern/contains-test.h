#include "hext/pattern/ContainsTest.h"


namespace {


TEST(Pattern_ContainsTest, Succeeds)
{
  {
    hext::ContainsTest t("word");
    EXPECT_TRUE(t.test("word"));
    EXPECT_TRUE(t.test("sword"));
    EXPECT_TRUE(t.test("words"));
    EXPECT_TRUE(t.test("asd words asd"));
    EXPECT_TRUE(t.test("asdwordasd"));
  }
}

TEST(Pattern_ContainsTest, Fails)
{
  {
    hext::ContainsTest t("word");
    EXPECT_FALSE(t.test("ward"));
    EXPECT_FALSE(t.test("sord"));
    EXPECT_FALSE(t.test("wrd"));
    EXPECT_FALSE(t.test("wor"));
    EXPECT_FALSE(t.test("nope nope nope"));
  }
}


} // namespace

