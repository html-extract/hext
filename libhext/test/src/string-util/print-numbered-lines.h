
TEST(StringUtil_PrintNumberedLines, Empty)
{
  const char * dummy = "dummy";
  std::stringstream ss;
  PrintNumberedLines(dummy, dummy, ss);
  EXPECT_TRUE(ss.str().empty());
}

TEST(StringUtil_PrintNumberedLines, PrintsNumbers)
{
  const char * begin = "This\nis\na\nstring\nin\na\nsentence\n";
  const char * end = begin + std::strlen(begin);
  std::string expected =
    "1: This\n"
    "2: is\n"
    "3: a\n"
    "4: string\n"
    "5: in\n"
    "6: a\n"
    "7: sentence\n"
    "8: \n";

  std::stringstream ss;
  PrintNumberedLines(begin, end, ss);
  std::string result = ss.str();
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(expected, result);
}

