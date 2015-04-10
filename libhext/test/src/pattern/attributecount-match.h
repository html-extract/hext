#include "hext/pattern/AttributeCountMatch.h"

#include "test-helper/html.h"


namespace {


TEST(Pattern_AttributeCountMatch, Matches)
{
  {
    helper::Html h("<html><head></head><body></body></html>");
    hext::AttributeCountMatch p(0);
    auto res = p.matches(h.body());
    EXPECT_TRUE(res.first);
  }

  {
    helper::Html h("<html><head></head><body attr='attr'></body></html>");
    hext::AttributeCountMatch p(1);
    auto res = p.matches(h.body());
    EXPECT_TRUE(res.first);
  }

  {
    helper::Html h("<html><head></head>\
<body attr1='attr' attr2='attr'></body></html>");
    hext::AttributeCountMatch p(2);
    auto res = p.matches(h.body());
    EXPECT_TRUE(res.first);
  }
}

TEST(Pattern_AttributeCountMatch, Fails)
{
  {
    helper::Html h("<html><head></head><body></body></html>");

    for(int i = 1; i < 10; ++i)
    {
      hext::AttributeCountMatch p(i);
      auto res = p.matches(h.body());
      EXPECT_FALSE(res.first);
    }
  }

  {
    helper::Html h("<html><head></head><body attr='attr'></body></html>");

    for(int i = -10; i < 1; ++i)
    {
      hext::AttributeCountMatch p(i);
      auto res = p.matches(h.body());
      EXPECT_FALSE(res.first);
    }
  }
}


} // namespace

