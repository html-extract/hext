
TEST(Pattern_ContainsWordsTest, Succeeds)
{
  {
    ContainsWordsTest t("word");
    EXPECT_TRUE(t.test("word"));
    EXPECT_TRUE(t.test("word "));
    EXPECT_TRUE(t.test("word a"));
    EXPECT_TRUE(t.test("sword word a"));
    EXPECT_TRUE(t.test(" word"));
    EXPECT_TRUE(t.test("a word"));
  }

  {
    ContainsWordsTest from_str("one two");
    ContainsWordsTest from_vec(std::vector<std::string>{"one", "two"});

    for(const auto& t : {from_str, from_vec})
    {
      EXPECT_TRUE(t.test("one two"));
      EXPECT_TRUE(t.test("two one"));
      EXPECT_TRUE(t.test("one two three"));
      EXPECT_TRUE(t.test("three two one"));
    }
  }
}

TEST(Pattern_ContainsWordsTest, Fails)
{
  {
    ContainsWordsTest t("word");
    EXPECT_FALSE(t.test("words"));
    EXPECT_FALSE(t.test("sword"));
    EXPECT_FALSE(t.test("swords"));
    EXPECT_FALSE(t.test("swordsword"));
    EXPECT_FALSE(t.test("wrd"));
    EXPECT_FALSE(t.test("wor"));
  }

  {
    ContainsWordsTest from_str("one two");
    ContainsWordsTest from_vec(std::vector<std::string>{"one", "two"});

    for(const auto& t : {from_str, from_vec})
    {
      EXPECT_FALSE(t.test("onetwo"));
      EXPECT_FALSE(t.test("twoone "));
      EXPECT_FALSE(t.test(" one twothree"));
      EXPECT_FALSE(t.test("threetwoone"));
    }
  }
}

