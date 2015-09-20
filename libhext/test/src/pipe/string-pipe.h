
TEST(Pattern_StringPipe, Copies)
{
  TrimPipe pipe(" ");
  pipe.emplace<TrimPipe>("sr");
  pipe.emplace<TrimPipe>("t");
  pipe.emplace<TrimPipe>("#");

  {
    TrimPipe other = pipe;
    EXPECT_EQ(other.pipe("  st#center#r  "), "center");
    other.emplace<TrimPipe>("c");
    EXPECT_EQ(pipe.pipe("  st#center#r  "), "center");
    EXPECT_EQ(other.pipe("  st#center#r  "), "enter");
  }

  {
    TrimPipe other;
    other = pipe;
    EXPECT_EQ(other.pipe("  st#center#r  "), "center");
    other.emplace<TrimPipe>("c");
    EXPECT_EQ(pipe.pipe("  st#center#r  "), "center");
    EXPECT_EQ(other.pipe("  st#center#r  "), "enter");
  }

  EXPECT_EQ(pipe.pipe("  st#center#r  "), "center");
}

