
TEST(Pattern_BeginsWithTest, Succeeds)
{
  {
    BeginsWithTest t("word");
    EXPECT_TRUE(t.test("word"));
    EXPECT_TRUE(t.test("words"));
    EXPECT_TRUE(t.test("word s"));
  }

  {
    BeginsWithTest t(" ");
    EXPECT_TRUE(t.test(" "));
    EXPECT_TRUE(t.test(" word"));
  }
}

TEST(Pattern_BeginsWithTest, Fails)
{
  BeginsWithTest t("word");
  EXPECT_FALSE(t.test("w"));
  EXPECT_FALSE(t.test("wo"));
  EXPECT_FALSE(t.test("wor"));
  EXPECT_FALSE(t.test("swords"));
  EXPECT_FALSE(t.test("sword"));
  EXPECT_FALSE(t.test("Word"));
}

