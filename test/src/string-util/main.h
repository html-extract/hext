#include "hext/string-util.h"

#include <string>
#include <cstring>
#include <limits>
#include <vector>
#include <sstream>


namespace {


TEST(String_TrimAndCollapseWs, EmptyString)
{
  EXPECT_EQ(hext::TrimAndCollapseWs(""), "");
  EXPECT_EQ(hext::TrimAndCollapseWs(" "), "");
  EXPECT_EQ(hext::TrimAndCollapseWs("  "), "");
  EXPECT_EQ(hext::TrimAndCollapseWs("   "), "");
}

TEST(String_TrimAndCollapseWs, AlreadyTrimmed)
{
  EXPECT_EQ(hext::TrimAndCollapseWs("a"), "a");
}

TEST(String_TrimAndCollapseWs, Trim)
{
  EXPECT_EQ(hext::TrimAndCollapseWs(" \n left"), "left");
  EXPECT_EQ(hext::TrimAndCollapseWs("right \n "), "right");
  EXPECT_EQ(hext::TrimAndCollapseWs("   \t leftright \n "), "leftright");
}

TEST(String_TrimAndCollapseWs, Collapse)
{
  std::vector<std::pair<std::string, std::string>> checks = {
    {"   \t l  e ftr    ig \n\t\r ht \n ", "l e ftr ig ht"},
    {"left           right", "left right"},
    {"left           right ", "left right"},
    {"left\nright", "left right"},
    {"left right", "left right"}
  };

  for(const auto& p : checks)
  {
    EXPECT_EQ(hext::TrimAndCollapseWs(p.first), p.second);
  }
}

TEST(String_IsSpace, DidntChangeBehaviour)
{
  char c_min = std::numeric_limits<char>::min();
  char c_max = std::numeric_limits<char>::max();
  std::vector<char> allowed_spaces = {' ','\t','\n','\f','\r'};

  for(int i = c_min; i <= c_max; ++i)
  {
    bool is_space = hext::IsSpace(i);
    bool expected = std::find(
      allowed_spaces.begin(),
      allowed_spaces.end(),
      static_cast<char>(i)
    ) != allowed_spaces.end();
    EXPECT_EQ(is_space, expected);
  }
}

TEST(String_GetCharName, DidntChangeBehaviour)
{
  char c_min = std::numeric_limits<char>::min();
  char c_max = std::numeric_limits<char>::max();

  for(int i = c_min; i <= c_max; ++i)
  {
    std::string char_name = hext::GetCharName(i);
    ASSERT_TRUE(char_name.size());
    if( char_name.size() > 1 )
    {
      EXPECT_EQ(char_name.front(), '[');
      EXPECT_EQ(char_name.back(), ']');
    }
    else
    {
      EXPECT_EQ(char_name.front(), (char)i);
    }
  }
}

TEST(String_GetCharPosition, Nullptr)
{
  const char * begin = "This\nis\na\nstring\nin\na\nsentence\n";
  const char * middle = begin + strlen(begin) / 2;
  const char * end = begin + strlen(begin);

  hext::CharPosPair nullpair = hext::CharPosPair(0, 0);
  EXPECT_EQ(hext::GetCharPosition(nullptr, middle, end), nullpair);
  EXPECT_EQ(hext::GetCharPosition(begin, nullptr, end), nullpair);
  EXPECT_EQ(hext::GetCharPosition(begin, middle, nullptr), nullpair);
}

TEST(String_GetCharPosition, Range)
{
  const char * begin = "This\nis\na\nstring\nin\na\nsentence\n";
  const char * middle = begin + strlen(begin) / 2;
  const char * end = begin + strlen(begin);

  hext::CharPosPair nullpair = hext::CharPosPair(0, 0);
  EXPECT_EQ(hext::GetCharPosition(begin, end, middle), nullpair);
  EXPECT_EQ(hext::GetCharPosition(end, middle, begin), nullpair);
  EXPECT_EQ(hext::GetCharPosition(middle, end, begin), nullpair);
  EXPECT_EQ(hext::GetCharPosition(begin, middle, begin), nullpair);
  EXPECT_EQ(hext::GetCharPosition(begin, begin, begin), nullpair);
}

TEST(String_GetCharPosition, Position)
{
  const char * begin = "This\nis\na\nstring\nin\na\nsentence\n";
  const char * end = begin + std::strlen(begin);
  int char_count = 0;
  int line_count = 0;

  for(const char * c = begin; c < end; ++c)
  {
    EXPECT_EQ(hext::GetCharPosition(c, begin, end), hext::CharPosPair(line_count, char_count));
    char_count++;
    if( *c == '\n' )
    {
      line_count++;
      char_count = 0;
    }
  }
}

TEST(String_GetDecNumberWidth, Width)
{
  EXPECT_EQ(hext::GetDecNumberWidth(0), 1);
  EXPECT_EQ(hext::GetDecNumberWidth(1), 1);
  EXPECT_EQ(hext::GetDecNumberWidth(9), 1);
  EXPECT_EQ(hext::GetDecNumberWidth(10), 2);
  EXPECT_EQ(hext::GetDecNumberWidth(99), 2);
  EXPECT_EQ(hext::GetDecNumberWidth(100), 3);
  EXPECT_EQ(hext::GetDecNumberWidth(-1), 1);
  EXPECT_EQ(hext::GetDecNumberWidth(-9), 1);
  EXPECT_EQ(hext::GetDecNumberWidth(-10), 2);
  EXPECT_EQ(hext::GetDecNumberWidth(-99), 2);
  EXPECT_EQ(hext::GetDecNumberWidth(-100), 3);
}

TEST(String_PrintWithLineNumbers, Nullptr)
{
  const char * dummy = "dummy";
  std::stringstream ss;
  hext::PrintWithLineNumbers(nullptr, nullptr, 0, ss);
  EXPECT_TRUE(ss.str().empty());

  hext::PrintWithLineNumbers(dummy, nullptr, 0, ss);
  EXPECT_TRUE(ss.str().empty());

  hext::PrintWithLineNumbers(nullptr, dummy, 0, ss);
  EXPECT_TRUE(ss.str().empty());
}

TEST(String_PrintWithLineNumbers, Empty)
{
  const char * dummy = "dummy";
  std::stringstream ss;
  hext::PrintWithLineNumbers(dummy, dummy, 0, ss);
  EXPECT_TRUE(ss.str().empty());
}

TEST(String_PrintWithLineNumbers, Lines)
{
  const char * begin = "This\nis\na\nstring\nin\na\nsentence\n";
  const char * end = begin + std::strlen(begin);
  std::string expected =
    "1: This\n"
    "2: is\n"
    "3: a\n"
    "4: string\n"
    "5: in\n"
    "6: a\n"
    "7: sentence\n"
    "8: \n";

  int line_count = std::count(begin, end, '\n');
  int number_width = hext::GetDecNumberWidth(line_count);
  std::stringstream ss;
  hext::PrintWithLineNumbers(begin, end, number_width, ss);
  std::string result = ss.str();
  EXPECT_FALSE(result.empty());
  EXPECT_EQ(expected, result);
}


} // namespace

