#include "boost/range/irange.hpp"

TEST(Pattern_ChildCountMatch, Matches)
{
  {
    THtml h("<div></div>");
    EXPECT_TRUE(ChildCountMatch(-1).matches(h.first()));
    EXPECT_TRUE(ChildCountMatch(0).matches(h.first()));
  }

  {
    THtml h(
      "<div>\
        <hr>\
        <hr>\
        <hr>\
        <hr>\
        <hr>\
      </div>");
    EXPECT_TRUE(ChildCountMatch(5).matches(h.first()));
  }
}

TEST(Pattern_ChildCountMatch, Fails)
{
  THtml h(
    "<div>\
      <hr>\
      <hr>\
      <hr>\
      <hr>\
      <hr>\
    </div>");

  auto range = boost::irange(-10, 10);
  for(int i : range)
    if( i != 5 )
      EXPECT_FALSE(ChildCountMatch(i).matches(h.first()));
}

