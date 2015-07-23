
TEST(ParseHext_ParseHext, ExampleFromDocumentation)
{
  try
  {
    Rule rule = ParseHext("<a href={href}/>");
  }
  catch( SyntaxError& )
    {}

  std::string hext_str("<a href={href}/>");
  try
  {
    Rule rule = ParseHext(hext_str.c_str(), hext_str.size());
  }
  catch( SyntaxError& )
    {}
}

TEST(ParseHext_ParseHext, ThrowsSyntaxError)
{
  EXPECT_THROW(ParseHext("invalid"), SyntaxError);
}

