
TEST(Pattern_ChildCountMatch, Matches)
{
  {
    THtml h("<div></div>");
    EXPECT_TRUE(ChildCountMatch(0).matches(h.first()));
  }

  {
    THtml h(
      "<div>\
        <hr>\
        <hr>\
        <hr>\
        <hr>\
        <hr>\
      </div>");
    EXPECT_TRUE(ChildCountMatch(5).matches(h.first()));
  }
}

TEST(Pattern_ChildCountMatch, Fails)
{
  THtml h(
    "<div>\
      <hr>\
      <hr>\
      <hr>\
      <hr>\
      <hr>\
    </div>");

  for(unsigned int i : {1u,2u,3u,4u,6u,7u,8u,9u,10u})
    EXPECT_FALSE(ChildCountMatch(i).matches(h.first()));
}

