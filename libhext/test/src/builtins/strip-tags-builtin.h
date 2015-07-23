
TEST(Builtins_StripTagsBuiltin, StripsTags)
{
  THtml h("<div> like<div>a</div>rolling  stone</div>");
  EXPECT_EQ(StripTagsBuiltin(h.root()), " likearolling  stone");
}

