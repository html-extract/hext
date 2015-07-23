#include <memory>

TEST(Pattern_FunctionMatch, Matches)
{
  auto test = std::make_unique<EqualsTest>("Inner Text");

  THtml h("<div>Inner Text</div>");
  EXPECT_TRUE(FunctionMatch(TextBuiltin, std::move(test)).matches(h.first()));
}

TEST(Pattern_FunctionMatch, Fails)
{
  auto test = std::make_unique<EqualsTest>("Inner Text");

  THtml h("<div>Nope</div>");
  EXPECT_FALSE(FunctionMatch(TextBuiltin, std::move(test)).matches(h.first()));
}

TEST(Pattern_FunctionMatch, CustomFunction)
{
  const char * secret = "secret";
  auto test = std::make_unique<EqualsTest>(secret);

  CaptureFunction my_func = [secret](const GumboNode *) { return secret; };

  THtml h("<div>dummy</div>");
  EXPECT_TRUE(FunctionMatch(my_func, std::move(test)).matches(h.first()));
}

