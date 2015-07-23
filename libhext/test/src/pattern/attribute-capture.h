
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
  AttributeCapture p("class", "result", boost::regex("class-(.*)"));
  auto pair = p.capture(h.first());
  EXPECT_TRUE(pair);
  EXPECT_EQ(pair->first, "result");
  EXPECT_EQ(pair->second, "value");
}

TEST(Pattern_AttributeCapture, CapturesAllWithNoCapRegex)
{
  THtml h("<div class='class-value'></div>");
  AttributeCapture p("class", "result", boost::regex("ss-.*"));
  auto pair = p.capture(h.first());
  EXPECT_TRUE(pair);
  EXPECT_EQ(pair->first, "result");
  EXPECT_EQ(pair->second, "ss-value");
}

TEST(Pattern_AttributeCapture, MissingAttrReturnsEmpty)
{
  THtml h("<div nope='nope'></div>");
  AttributeCapture p("class", "result");
  auto pair = p.capture(h.first());
  EXPECT_FALSE(pair);
}

