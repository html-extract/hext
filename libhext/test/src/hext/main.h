#include "hext/Hext.h"


namespace {


TEST(Hext_Hext, DoesNotHideParseErrors)
{
  EXPECT_THROW(hext::Hext("invalid"), hext::ParseError);
}

TEST(Hext_Hext, Extracts)
{
  hext::Hext h("<a href={link}>");

  auto v = h.extract(R"(
    <div>
      <a href="one"></a>
      <a href="two"></a>
      <a href="three"></a>
    </div>
  )");

  int i = 0;
  const char * arr[] = {"one", "two", "three"};
  EXPECT_EQ(v.size(), 3);
  for(const auto& map : v)
  {
    EXPECT_EQ(map.size(), 1);
    const char * expected_value = arr[i++];
    EXPECT_EQ(map.begin()->first, "link");
    EXPECT_EQ(map.begin()->second, expected_value); 
  }
}


} // namespace

