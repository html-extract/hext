#include "hext/pattern/BuiltinMatch.h"
#include "hext/pattern/LiteralTest.h"

#include "test-helper/html.h"


namespace {


TEST(Pattern_BuiltinMatch, Matches)
{
  helper::Html h("<html><head></head><body>Inner Text</body></html>");
  auto test = hext::MakeUnique<hext::LiteralTest>("Inner Text");
  hext::BuiltinMatch p(hext::GetNodeText, std::move(test));
  auto res = p.matches(h.body());
  EXPECT_TRUE(res.first);
}

TEST(Pattern_BuiltinMatch, Fails)
{
  helper::Html h("<html><head></head><body>Inner Text</body></html>");
  auto test = hext::MakeUnique<hext::LiteralTest>("Inner Texts");
  hext::BuiltinMatch p(hext::GetNodeText, std::move(test));
  auto res = p.matches(h.body());
  EXPECT_FALSE(res.first);
}


} // namespace

