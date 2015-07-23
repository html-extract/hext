
TEST(Pattern_ContainsTest, Succeeds)
{
  ContainsTest t("word");
  EXPECT_TRUE(t.test("word"));
  EXPECT_TRUE(t.test("words"));
  EXPECT_TRUE(t.test("sword"));
  EXPECT_TRUE(t.test("swords"));
  EXPECT_TRUE(t.test("aa words aa"));
  EXPECT_TRUE(t.test("aawordaa"));
}

TEST(Pattern_ContainsTest, Fails)
{
  ContainsTest t("word");
  EXPECT_FALSE(t.test("ward"));
  EXPECT_FALSE(t.test("sord"));
  EXPECT_FALSE(t.test("wrd"));
  EXPECT_FALSE(t.test("wor"));
  EXPECT_FALSE(t.test("nope nope nope"));
}

