#include "hext/pattern/ValueTest.h"


namespace {


TEST(Pattern_ValueTest, Succeeds)
{
  hext::ValueTest t;
  EXPECT_TRUE(t.test(""));
  EXPECT_TRUE(t.test("yes"));
  EXPECT_TRUE(t.test("this"));
  EXPECT_TRUE(t.test("test"));
  EXPECT_TRUE(t.test("is"));
  EXPECT_TRUE(t.test("pretty"));
  EXPECT_TRUE(t.test("much"));
  EXPECT_TRUE(t.test("useless"));
  EXPECT_TRUE(t.test(":)"));
  EXPECT_TRUE(t.test("A ValueTest always succeeds."));
}


} // namespace

