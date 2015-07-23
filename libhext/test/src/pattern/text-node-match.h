
TEST(Pattern_TextNodeMatch, Matches)
{
  TextNodeMatch m;

  THtml h("Text");
  EXPECT_TRUE(m.matches(h.first()));
}

TEST(Pattern_TextNodeMatch, Fails)
{
  TextNodeMatch m;

  THtml h("<b>HTML element</b>");
  EXPECT_FALSE(m.matches(h.first()));
}


