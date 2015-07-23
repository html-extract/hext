
TEST(Html_Html, ExampleFromDocumentation)
{
  Html page("<html><body>This is a string containing html</body></html>");
  const GumboNode * root = page.root();
  EXPECT_TRUE(root);

  Rule html_root(HtmlTag::HTML);
  EXPECT_TRUE(html_root.matches(root));
}

