#include <cstring>

TEST(StringUtil_CharPosition, Position)
{
  const char * begin = "This\nis\na\nstring\nin\na\nsentence\n";
  const char * end = begin + std::strlen(begin);
  int char_count = 0;
  int line_count = 0;

  for(const char * c = begin; c != end; ++c)
  {
    EXPECT_EQ(CharPosition(begin, c), CharPosPair(line_count, char_count));
    if( *c == '\n' )
    {
      line_count++;
      char_count = 0;
    }
    else
    {
      char_count++;
    }
  }
}

