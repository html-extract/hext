
TEST(Pattern_OnlyChildMatch, Matches)
{
  {
    THtml h("<div><b></b><b></b></div>");
    OnlyChildMatch m;
    EXPECT_TRUE(m.matches(h.first()));
  }

  {
    THtml h("<b></b><div></div>");
    OnlyChildMatch m(OnlyChildMatch::OfType);
    EXPECT_TRUE(m.matches(h.body_child(1)));
    EXPECT_TRUE(m.matches(h.body_child(2)));
  }
}

TEST(Pattern_OnlyChildMatch, Fails)
{
  {
    THtml h("<b></b><b></b>");
    OnlyChildMatch m;
    EXPECT_FALSE(m.matches(h.first()));
  }

  {
    THtml h("<b></b><b></b>");
    OnlyChildMatch m(OnlyChildMatch::OfType);
    EXPECT_FALSE(m.matches(h.body_child(1)));
    EXPECT_FALSE(m.matches(h.body_child(2)));
  }
}

