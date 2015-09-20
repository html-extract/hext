
TEST(Pattern_AppendPipe, Appends)
{
  AppendPipe def("content");
  EXPECT_EQ(def.transform("Content: "), "Content: content");
}

