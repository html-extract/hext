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
    EXPECT_TRUE(p.matches(h.body()));
  }

  {
    helper::Html h("<html><head></head><body></body></html>");
    hext::ChildCountMatch p(0);
    EXPECT_TRUE(p.matches(h.body()));
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
    EXPECT_FALSE(p.matches(h.body()));
  }

  {
    hext::ChildCountMatch p(4);
    EXPECT_FALSE(p.matches(h.body()));
  }

  {
    hext::ChildCountMatch p(0);
    EXPECT_FALSE(p.matches(h.body()));
  }
}


} // namespace

