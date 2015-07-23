#include <memory>

TEST(Pattern_AttributeMatch, Matches)
{
  auto test = std::make_unique<EqualsTest>("value");

  THtml h("<div class='value'></div>");
  EXPECT_TRUE(AttributeMatch("class").matches(h.first()));
  EXPECT_TRUE(AttributeMatch("class", std::move(test)).matches(h.first()));
}

TEST(Pattern_AttributeMatch, Fails)
{
  auto test = std::make_unique<EqualsTest>("value");

  THtml h("<div class='nope'></div>");
  EXPECT_FALSE(AttributeMatch("clas").matches(h.first()));
  EXPECT_FALSE(AttributeMatch("nope").matches(h.first()));
  EXPECT_FALSE(AttributeMatch("class", std::move(test)).matches(h.first()));
}

