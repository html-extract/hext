#include "hext/pattern/IsNotRegexTest.h"


namespace {


TEST(Pattern_IsNotRegexTest, Succeeds)
{
  {
    hext::IsNotRegexTest t(boost::regex("^word$"));
    EXPECT_TRUE(t.test("worda"));
    EXPECT_TRUE(t.test("aword"));
    EXPECT_TRUE(t.test("aworda"));
    EXPECT_TRUE(t.test("else"));
  }
}

TEST(Pattern_IsNotRegexTest, Fails)
{
  {
    hext::IsNotRegexTest t(boost::regex("word"));
    EXPECT_FALSE(t.test("word"));
    EXPECT_FALSE(t.test("a word"));
    EXPECT_FALSE(t.test("a sword"));
    EXPECT_FALSE(t.test("a sword "));
  }

  {
    hext::IsNotRegexTest t(boost::regex("^s?w(o|ei)rd$"));
    EXPECT_FALSE(t.test("word"));
    EXPECT_FALSE(t.test("sword"));
    EXPECT_FALSE(t.test("weird"));
    EXPECT_FALSE(t.test("sweird"));
  }
}


} // namespace

