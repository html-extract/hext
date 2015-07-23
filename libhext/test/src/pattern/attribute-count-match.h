
TEST(Pattern_AttributeCountMatch, Matches)
{
  {
    THtml h("<div></div>");
    EXPECT_TRUE(AttributeCountMatch(0).matches(h.first()));
  }

  {
    THtml h("<div attr='attr'></div>");
    EXPECT_TRUE(AttributeCountMatch(1).matches(h.first()));
  }

  {
    THtml h("<div attr1='attr1' attr2='attr2'></div>");
    EXPECT_TRUE(AttributeCountMatch(2).matches(h.first()));
  }
}

TEST(Pattern_AttributeCountMatch, Fails)
{
  {
    THtml h("<div></div>");
    for(unsigned int i = 1; i < 10; ++i)
      EXPECT_FALSE(AttributeCountMatch(i).matches(h.first()));
  }

  {
    THtml h("<div attr='attr'></div>");
    EXPECT_FALSE(AttributeCountMatch(0).matches(h.first()));
    for(unsigned int i = 2; i < 10; ++i)
      EXPECT_FALSE(AttributeCountMatch(i).matches(h.first()));
  }
}

