
TEST(Pattern_AttributeCapture, Captures)
{
  THtml h("<div class='class-value'></div>");
  AttributeCapture p("class", "result");
  auto pair = p.capture(h.first());
  EXPECT_TRUE(pair);
  EXPECT_EQ(pair->first, "result");
  EXPECT_EQ(pair->second, "class-value");
}

TEST(Pattern_AttributeCapture, CapturesWithRegex)
{
  THtml h("<div class='class-value'></div>");
  AttributeCapture p(
      "class",
      "result",
      std::make_unique<RegexPipe>(boost::regex("class-(.*)")));
  auto pair = p.capture(h.first());
  EXPECT_TRUE(pair);
  EXPECT_EQ(pair->first, "result");
  EXPECT_EQ(pair->second, "value");
}

TEST(Pattern_AttributeCapture, MissingAttrReturnsEmpty)
{
  THtml h("<div nope='nope'></div>");
  AttributeCapture p("class", "result");
  auto pair = p.capture(h.first());
  EXPECT_FALSE(pair);
}

TEST(Pattern_AttributeCapture, ExampleFromDocumentation)
{
  {
    THtml h("<img src='bob.jpg'/>");
    AttributeCapture img("src", "image");
    auto result = img.capture(h.first());
    ASSERT_TRUE(result);
    EXPECT_EQ(*result, ResultPair("image", "bob.jpg"));
  }

  {
    THtml h("<a href='/highway-61'></a>");
    AttributeCapture highway(
        "href",
        "U.S. Route",
        std::make_unique<RegexPipe>(boost::regex("\\d+")));
    auto result = highway.capture(h.first());
    ASSERT_TRUE(result);
    EXPECT_EQ(*result, ResultPair("U.S. Route", "61"));
  }
}

