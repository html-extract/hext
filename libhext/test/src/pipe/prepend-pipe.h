
TEST(Pattern_PrependPipe, Prepends)
{
  PrependPipe def("Content: ");
  EXPECT_EQ(def.transform("content"), "Content: content");
}

