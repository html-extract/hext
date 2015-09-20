
TEST(Pipe_CasePipe, ChangesCase)
{
  {
    CasePipe p;
    EXPECT_EQ(p.transform("Word"), "word");
  }
  {
    CasePipe p(CasePipe::ToLower);
    EXPECT_EQ(p.transform("WoRd"), "word");
  }
  {
    CasePipe p(CasePipe::ToUpper);
    EXPECT_EQ(p.transform("Word"), "WORD");
  }
}

