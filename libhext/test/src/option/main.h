#include "hext/Option.h"


namespace {


hext::Option c_opt(int i)
{
  return static_cast<hext::Option>(i);
}

int c_int(hext::Option o)
{
  return static_cast<int>(o);
}

TEST(Option_Bitops, OR)
{
  int left = 2;
  int right = 1;
  int expected = ( left | right );

  EXPECT_EQ(c_int(c_opt(left) | c_opt(right)), expected);
}

TEST(Option_Bitops, AND)
{
  int left = 256;
  int right = 128;
  int expected = ( left & right );

  EXPECT_EQ(c_int(c_opt(left) & c_opt(right)), expected);
}

TEST(Option_Bitops, XOR)
{
  int left = 255;
  int right = 128;
  int expected = ( left ^ right );

  EXPECT_EQ(c_int(c_opt(left) ^ c_opt(right)), expected);
}

TEST(Option_Bitops, NOT)
{
  int left = 255;
  int expected = ~left;
  EXPECT_EQ(c_int(~c_opt(left)), expected);
}

TEST(Option_Bitops, OR_ASSIGN)
{
  int left = 2;
  int right = 1;
  int expected = ( left | right );
  hext::Option o = c_opt(left);
  o |= c_opt(right);
  EXPECT_EQ(c_int(o), expected);
}

TEST(Option_Bitops, AND_ASSIGN)
{
  int left = 256;
  int right = 128;
  int expected = ( left & right );
  hext::Option o = c_opt(left);
  o &= c_opt(right);
  EXPECT_EQ(c_int(o), expected);
}

TEST(Option_Bitops, XOR_ASSIGN)
{
  int left = 255;
  int right = 128;
  int expected = ( left ^ right );
  hext::Option o = c_opt(left);
  o ^= c_opt(right);
  EXPECT_EQ(c_int(o), expected);
}


} // namespace

