#include <memory>

TEST(Pattern_NegateMatch, Matches)
{
  NegateMatch no_href;
  no_href.append_match(std::make_unique<AttributeMatch>("href"));

  THtml h("<a class='dummy'></a>");
  EXPECT_TRUE(no_href.matches(h.first()));
  EXPECT_TRUE(NegateMatch(std::make_unique<AttributeMatch>("href")).matches(h.first()));
}

TEST(Pattern_NegateMatch, Fails)
{
  NegateMatch no_href;
  no_href.append_match(std::make_unique<AttributeMatch>("href"));

  THtml h("<a href='dummy'></a>");
  EXPECT_FALSE(no_href.matches(h.first()));
  EXPECT_FALSE(NegateMatch(std::make_unique<AttributeMatch>("href")).matches(h.first()));
}

