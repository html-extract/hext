#include "hext/file.h"

#include <fstream>
#include <sstream>


namespace hext {


TEST(File_ReadFileOrThrow, Throw)
{
  EXPECT_THROW(hext::ReadFileOrThrow(""), hext::FileError);
}

TEST(File_ReadFileOrThrow, ReadFile)
{
  std::string contents = hext::ReadFileOrThrow(__FILE__);
  ASSERT_TRUE(contents.size());

  std::ifstream file(__FILE__, std::ios::in | std::ios::binary);
  ASSERT_TRUE(file.good());
  std::stringstream buffer;
  buffer << file.rdbuf();

  std::string expected = buffer.str();
  ASSERT_TRUE(expected.size());

  EXPECT_EQ(expected, contents);
}


} // hext

