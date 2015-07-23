
TEST(Pattern_EqualsTest, Succeeds)
{
  {
    EqualsTest t("word");
    EXPECT_TRUE(t.test("word"));
  }

  {
    EqualsTest t("");
    EXPECT_TRUE(t.test(""));
  }
}

TEST(Pattern_EqualsTest, Fails)
{
  {
    EqualsTest t("word");
    EXPECT_FALSE(t.test("words"));
    EXPECT_FALSE(t.test("sword"));
    EXPECT_FALSE(t.test("wrd"));
    EXPECT_FALSE(t.test("wor"));
  }

  {
    EqualsTest t("");
    EXPECT_FALSE(t.test("w"));
    EXPECT_FALSE(t.test("word"));
  }
}

