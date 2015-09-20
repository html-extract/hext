
TEST(Pattern_RegexReplacePipe, Replaces)
{
  {
    RegexReplacePipe r(boost::regex("Number \\d+"), "Number 23");
    EXPECT_EQ(r.transform("My Number? Number 42"), "My Number? Number 23");
  }
  {
    RegexReplacePipe r(boost::regex("Number"), "Potato");
    EXPECT_EQ(r.transform("My Number? Number 42"), "My Potato? Potato 42");
  }
  {
    RegexReplacePipe r(boost::regex(" Number"), "");
    EXPECT_EQ(r.transform("My Number? Number 42"), "My? 42");
  }
}

TEST(Pattern_RegexReplacePipe, ExampleFromDocumentation)
{
  RegexReplacePipe r(boost::regex("^(\\w+) (\\w+)$"), "$2 $1");
  EXPECT_EQ(r.transform("first second"), "second first");
}

