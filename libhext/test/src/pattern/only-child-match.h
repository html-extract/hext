
TEST(Pattern_OnlyChildMatch, Matches)
{
  OnlyChildMatch m;

  THtml h("<div><b></b><b></b></div>");
  EXPECT_TRUE(m.matches(h.first()));
}

TEST(Pattern_OnlyChildMatch, Fails)
{
  OnlyChildMatch m;

  THtml h("<b></b><b></b>");
  EXPECT_FALSE(m.matches(h.first()));
}

