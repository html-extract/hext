
TEST(Pattern_FunctionMatch, Matches)
{
  THtml h("<div></div>");

  MatchFunction is_div = [](const GumboNode * node) {
    return node->type == GUMBO_NODE_ELEMENT &&
           node->v.element.tag == GUMBO_TAG_DIV;
  };

  EXPECT_TRUE(FunctionMatch(is_div).matches(h.first()));
}

TEST(Pattern_FunctionMatch, Fails)
{
  THtml h("<span></span>");

  MatchFunction is_div = [](const GumboNode * node) {
    return node->type == GUMBO_NODE_ELEMENT &&
           node->v.element.tag == GUMBO_TAG_DIV;
  };

  EXPECT_FALSE(FunctionMatch(is_div).matches(h.first()));
}

