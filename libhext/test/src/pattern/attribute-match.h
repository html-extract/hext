#include "hext/pattern/AttributeMatch.h"


namespace {


TEST(Pattern_AttributeMatch, Matches)
{
  helper::Html h("<html><head></head><body class='class-value'></body></html>");
  auto test = hext::MakeUnique<hext::LiteralTest>("class-value");
  hext::AttributeMatch p("class", std::move(test));
  EXPECT_TRUE(p.matches(h.body()));
}

TEST(Pattern_AttributeMatch, Fails)
{
  {
    helper::Html h("<html><head></head><body class='class-value'></body></html>");
    auto test_fail = hext::MakeUnique<hext::LiteralTest>("class-valu");
    hext::AttributeMatch p_fail("class", std::move(test_fail));
    EXPECT_FALSE(p_fail.matches(h.body()));
  }

  {
    helper::Html h("<html><head></head><body id='class-value'></body></html>");
    auto test_fail = hext::MakeUnique<hext::LiteralTest>("class-value");
    hext::AttributeMatch p_fail("class", std::move(test_fail));
    EXPECT_FALSE(p_fail.matches(h.body()));
  }
}


} // namespace

