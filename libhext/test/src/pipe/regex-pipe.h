
TEST(Pattern_RegexPipe, Filters)
{
  RegexPipe def(boost::regex("Number (\\d+)"));
  EXPECT_EQ(def.transform("Number 42"), "42");
}

TEST(Pattern_RegexPipe, ExamplesFromDocumentation)
{
  std::string input = "Highway 61 revisited";

  const std::pair<const char *, const char *> checks[] = {
    {"\\d+", "61"},
    {"Highway \\d+", "Highway 61"},
    {"Highway (\\d+)", "61"},
    {"\\w+", "Highway"},
    {"(\\w+) (\\d+)", "Highway"}
  };

  for(auto p : checks)
  {
    RegexPipe def(boost::regex(p.first));
    EXPECT_EQ(def.transform(input), p.second);
  }
}

