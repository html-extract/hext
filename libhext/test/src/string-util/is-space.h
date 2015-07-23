#include <limits>
#include <vector>

TEST(StringUtil_IsSpace, DidntChangeBehaviour)
{
  char c_min = std::numeric_limits<char>::min();
  char c_max = std::numeric_limits<char>::max();
  std::vector<char> allowed_spaces = {' ','\t','\n','\f','\r'};

  for(int i = c_min; i <= c_max; ++i)
  {
    bool is_space = IsSpace(static_cast<char>(i));
    bool expected = std::find(
      allowed_spaces.begin(),
      allowed_spaces.end(),
      static_cast<char>(i)
    ) != allowed_spaces.end();
    EXPECT_EQ(is_space, expected);
  }
}

