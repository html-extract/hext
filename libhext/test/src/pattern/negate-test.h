
TEST(Pattern_NegateTest, Succeeds)
{
  NegateTest t(std::make_unique<EqualsTest>("word"));
  EXPECT_TRUE(t.test("nope"));
}

TEST(Pattern_NegateTest, Fails)
{
  NegateTest t(std::make_unique<EqualsTest>("word"));
  EXPECT_FALSE(t.test("word"));
}

