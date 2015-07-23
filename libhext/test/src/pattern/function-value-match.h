#include <memory>

TEST(Pattern_FunctionValueMatch, Matches)
{
  auto test = std::make_unique<EqualsTest>("Inner Text");

  THtml h("<div>Inner Text</div>");
  EXPECT_TRUE(FunctionValueMatch(TextBuiltin, std::move(test)).matches(h.first()));
}

TEST(Pattern_FunctionValueMatch, Fails)
{
  auto test = std::make_unique<EqualsTest>("Inner Text");

  THtml h("<div>Nope</div>");
  EXPECT_FALSE(FunctionValueMatch(TextBuiltin, std::move(test)).matches(h.first()));
}

TEST(Pattern_FunctionValueMatch, CustomFunction)
{
  const char * secret = "secret";
  auto test = std::make_unique<EqualsTest>(secret);

  CaptureFunction my_func = [secret](const GumboNode *) { return secret; };

  THtml h("<div>dummy</div>");
  EXPECT_TRUE(FunctionValueMatch(my_func, std::move(test)).matches(h.first()));
}

