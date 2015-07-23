
TEST(Pattern_FunctionCapture, Captures)
{
  THtml h("<div>Inner Text</div>");
  FunctionCapture p(TextBuiltin, "result");
  auto pair = p.capture(h.first());
  EXPECT_TRUE(pair);
  EXPECT_EQ(pair->first, "result");
  EXPECT_EQ(pair->second, "Inner Text");
}

TEST(Pattern_FunctionCapture, CapturesWithRegex)
{
  THtml h("<div>Inner Text</div>");
  FunctionCapture p(
    TextBuiltin,
    "result",
    boost::regex("Inner (.*)")
  );
  auto pair = p.capture(h.first());
  EXPECT_TRUE(pair);
  EXPECT_EQ(pair->first, "result");
  EXPECT_EQ(pair->second, "Text");
}

TEST(Pattern_FunctionCapture, CapturesAllWithNoCapRegex)
{
  THtml h("<div>Inner Text</div>");
  FunctionCapture p(
    TextBuiltin,
    "result",
    boost::regex("Inner .*")
  );
  auto pair = p.capture(h.first());
  EXPECT_TRUE(pair);
  EXPECT_EQ(pair->first, "result");
  EXPECT_EQ(pair->second, "Inner Text");
}

TEST(Pattern_FunctionCapture, CustomFunction)
{
  const char * secret = "secret";
  CaptureFunction my_func = [secret](const GumboNode *) { return secret; };

  THtml h("<div>dummy</div>");
  for(auto reg : {boost::optional<boost::regex>(),
                  boost::optional<boost::regex>(boost::regex("[a-z]{6}"))})
  {
    FunctionCapture p(
      my_func,
      "result",
      reg
    );

    auto pair = p.capture(h.first());
    EXPECT_TRUE(pair);
    EXPECT_EQ(pair->first, "result");
    EXPECT_EQ(pair->second, "secret");
  }
}

