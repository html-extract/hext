#include "hext/pattern/ChildCountMatch.h"

#include "test-helper/html.h"


namespace {


TEST(Pattern_ChildCountMatch, Matches)
{
  {
    helper::Html h("<html><head></head><body>\
      <div></div>\
      <div></div>\
      <div></div>\
      <div></div>\
      <div></div>\
        </body></html>");
    hext::ChildCountMatch p(5);
    auto res = p.matches(h.body());
    EXPECT_TRUE(res.first);
  }

  {
    helper::Html h("<html><head></head><body></body></html>");
    hext::ChildCountMatch p(0);
    auto res = p.matches(h.body());
    EXPECT_TRUE(res.first);
  }
}

TEST(Pattern_ChildCountMatch, Fails)
{
  helper::Html h("<html><head></head><body>\
    <div></div>\
    <div></div>\
    <div></div>\
    <div></div>\
    <div></div>\
      </body></html>");
  {
    hext::ChildCountMatch p(6);
    auto res = p.matches(h.body());
    EXPECT_FALSE(res.first);
  }

  {
    hext::ChildCountMatch p(4);
    auto res = p.matches(h.body());
    EXPECT_FALSE(res.first);
  }

  {
    hext::ChildCountMatch p(0);
    auto res = p.matches(h.body());
    EXPECT_FALSE(res.first);
  }
}


} // namespace

