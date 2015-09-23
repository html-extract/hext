
TEST(ParseHext_ParseHext, ExampleFromDocumentation)
{
  EXPECT_NO_THROW(ParseHext("<a href:link />"));

  std::string hext_str("<a href:link />");
  EXPECT_NO_THROW(ParseHext(hext_str.c_str(), hext_str.size()));
}

TEST(ParseHext_ParseHext, ThrowsSyntaxError)
{
  EXPECT_THROW(ParseHext("invalid"), SyntaxError);
}

