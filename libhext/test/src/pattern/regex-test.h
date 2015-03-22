#include "hext/pattern/RegexTest.h"


namespace {


TEST(Pattern_RegexTest, Succeeds)
{
  {
    hext::RegexTest t(boost::regex("word"));
    EXPECT_TRUE(t.test("word"));
    EXPECT_TRUE(t.test("a word"));
    EXPECT_TRUE(t.test("a sword"));
    EXPECT_TRUE(t.test("a sword "));
  }

  {
    hext::RegexTest t(boost::regex("^s?w(o|ei)rd$"));
    EXPECT_TRUE(t.test("word"));
    EXPECT_TRUE(t.test("sword"));
    EXPECT_TRUE(t.test("weird"));
    EXPECT_TRUE(t.test("sweird"));
  }
}

TEST(Pattern_RegexTest, Fails)
{
  {
    hext::RegexTest t(boost::regex("^word$"));
    EXPECT_FALSE(t.test("worda"));
    EXPECT_FALSE(t.test("aword"));
    EXPECT_FALSE(t.test("aworda"));
    EXPECT_FALSE(t.test("else"));
  }
}


} // namespace

