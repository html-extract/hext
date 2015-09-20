
TEST(Pipe_TrimPipe, Trims)
{
  {
    TrimPipe def;
    EXPECT_EQ(def.transform("  str "), "str");
  }
  {
    TrimPipe t("t");
    EXPECT_EQ(t.transform("t"), "");
  }
}

