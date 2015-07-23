
TEST(Pattern_RegexTest, Succeeds)
{
  {
    RegexTest has_number(boost::regex("\\d+"));
    EXPECT_TRUE(has_number.test("Nr. 23!"));
    EXPECT_TRUE(has_number.test("23"));
  }

  {
    RegexTest is_date(boost::regex("^\\d{2}-\\d{2}-\\d{4}$"));
    EXPECT_TRUE(is_date.test("01-01-1970"));
    EXPECT_TRUE(is_date.test("19-01-2038"));
  }
}

TEST(Pattern_RegexTest, Fails)
{
  {
    RegexTest has_number(boost::regex("\\d+"));
    EXPECT_FALSE(has_number.test("foo"));
  }

  {
    RegexTest is_date(boost::regex("^\\d{2}-\\d{2}-\\d{4}$"));
    EXPECT_FALSE(is_date.test("09-09-99"));
    EXPECT_FALSE(is_date.test("Born on 09-09-1941."));
  }
}

