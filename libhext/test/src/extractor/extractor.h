
TEST(Extractor_Extractor, ExampleFromDocumentation)
{
  Extractor ext("<a href={href}/>");
  auto rt = ext.extract(
    "<a href='/link'>Link 1</a>"
    "<a href='/link'>Link 2</a>"
    "<a href='/link'>Link 3</a>"
  );
  auto result = rt->flatten();
  EXPECT_EQ(result.size(), 3);
  for(const auto& group : result)
    for(const auto& p : group)
    {
      EXPECT_EQ(p.first, "href");
      EXPECT_EQ(p.second, "/link");
    }
}

