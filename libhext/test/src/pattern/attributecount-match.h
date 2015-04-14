#include "hext/pattern/AttributeCountMatch.h"

#include "test-helper/html.h"


namespace {


TEST(Pattern_AttributeCountMatch, Matches)
{
  {
    helper::Html h("<html><head></head><body></body></html>");
    hext::AttributeCountMatch p(0);
    EXPECT_TRUE(p.matches(h.body()));
  }

  {
    helper::Html h("<html><head></head><body attr='attr'></body></html>");
    hext::AttributeCountMatch p(1);
    EXPECT_TRUE(p.matches(h.body()));
  }

  {
    helper::Html h("<html><head></head>\
<body attr1='attr' attr2='attr'></body></html>");
    hext::AttributeCountMatch p(2);
    EXPECT_TRUE(p.matches(h.body()));
  }
}

TEST(Pattern_AttributeCountMatch, Fails)
{
  {
    helper::Html h("<html><head></head><body></body></html>");

    for(int i = 1; i < 10; ++i)
    {
      hext::AttributeCountMatch p(i);
      EXPECT_FALSE(p.matches(h.body()));
    }
  }

  {
    helper::Html h("<html><head></head><body attr='attr'></body></html>");

    for(int i = -10; i < 1; ++i)
    {
      hext::AttributeCountMatch p(i);
      EXPECT_FALSE(p.matches(h.body()));
    }
  }
}


} // namespace

