
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

TEST(Pattern_FunctionCapture, RegexExampleFromDocumentation)
{
  THtml h("<div>Highway 61 revisited</div>");

  {
    auto result = FunctionCapture(TextBuiltin, "r", boost::regex("\\d+"))
                      .capture(h.first());
    ASSERT_TRUE(result);
    EXPECT_EQ(*result, ResultPair("r", "61"));
  }

  {
    auto result = FunctionCapture(TextBuiltin, "r", boost::regex("Highway \\d+"))
                      .capture(h.first());
    ASSERT_TRUE(result);
    EXPECT_EQ(*result, ResultPair("r", "Highway 61"));
  }

  {
    auto result = FunctionCapture(TextBuiltin, "r", boost::regex("Highway (\\d+)"))
                      .capture(h.first());
    ASSERT_TRUE(result);
    EXPECT_EQ(*result, ResultPair("r", "61"));
  }

  {
    auto result = FunctionCapture(TextBuiltin, "r", boost::regex("\\w+"))
                      .capture(h.first());
    ASSERT_TRUE(result);
    EXPECT_EQ(*result, ResultPair("r", "Highway"));
  }

  {
    auto result = FunctionCapture(TextBuiltin, "r", boost::regex("(\\w+) (\\d+)"))
                      .capture(h.first());
    ASSERT_TRUE(result);
    EXPECT_EQ(*result, ResultPair("r", "Highway"));
  }
}

TEST(Pattern_FunctionCapture, ExampleFromDocumentation)
{
  {
    THtml h("<div>5 reasons why foo is better than bar</div>");
    FunctionCapture text(TextBuiltin, "text");
    auto result = text.capture(h.first());
    ASSERT_TRUE(result);
    EXPECT_EQ(*result, ResultPair("text", "5 reasons why foo is better than bar"));
  }

  {
    THtml h("<div>The result is 25cm.</div>");
    FunctionCapture centimeters(InnerHtmlBuiltin,
                                "centimeters",
                                boost::regex("(\\d+)cm"));
    auto result = centimeters.capture(h.first());
    ASSERT_TRUE(result);
    EXPECT_EQ(*result, ResultPair("centimeters", "25"));
  }
}

