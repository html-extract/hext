#include "hext/pattern/NthChildMatch.h"

#include "test-helper/html.h"
#include "test-helper/node.h"


namespace {


const char * html =
"<html>"
  "<head></head>"
  "<body>"
    "<a    pos='1'  rev-pos='15' tag-pos='1' tag-rev-pos='8'></a>"
    "<h2   pos='2'  rev-pos='14' tag-pos='1' tag-rev-pos='1'></h2>"
    "<a    pos='3'  rev-pos='13' tag-pos='2' tag-rev-pos='7'></a>"
    "<span pos='4'  rev-pos='12' tag-pos='1' tag-rev-pos='2'></span>"
    "<div  pos='5'  rev-pos='11' tag-pos='1' tag-rev-pos='3'></div>"
    "<div  pos='6'  rev-pos='10' tag-pos='2' tag-rev-pos='2'></div>"
    "<a    pos='7'  rev-pos='9'  tag-pos='3' tag-rev-pos='6'></a>"
    "<a    pos='8'  rev-pos='8'  tag-pos='4' tag-rev-pos='5'></a>"
    "<span pos='9'  rev-pos='7'  tag-pos='2' tag-rev-pos='1'></span>"
    "<a    pos='10' rev-pos='6'  tag-pos='5' tag-rev-pos='4'></a>"
    "<a    pos='11' rev-pos='5'  tag-pos='6' tag-rev-pos='3'></a>"
    "<div  pos='12' rev-pos='4'  tag-pos='3' tag-rev-pos='1'></div>"
    "<a    pos='13' rev-pos='3'  tag-pos='7' tag-rev-pos='2'></a>"
    "<h1   pos='14' rev-pos='2'  tag-pos='1' tag-rev-pos='1'></h1>"
    "<a    pos='15' rev-pos='1'  tag-pos='8' tag-rev-pos='1'></a>"
  "</body>"
"</html>";

TEST(Pattern_NthChildMatch, MatchesWithoutStep)
{
  using helper::attr_value;
  using helper::tag;

  helper::Html h(html);
  const GumboNode * body = h.body();
  ASSERT_NE(body, nullptr);
  ASSERT_EQ(body->type, GUMBO_NODE_ELEMENT);

  const GumboVector& children = body->v.element.children;
  ASSERT_EQ(children.length, 15);

  for(unsigned int i = 0; i < children.length; ++i)
  {
    auto node = static_cast<const GumboNode *>(children.data[i]);
    ASSERT_EQ(node->type, GUMBO_NODE_ELEMENT);

    int pos = std::stoi(attr_value(node, "pos"));
    int rev_pos = std::stoi(attr_value(node, "rev-pos"));
    int tag_pos = std::stoi(attr_value(node, "tag-pos"));
    int tag_rev_pos = std::stoi(attr_value(node, "tag-rev-pos"));

    {
      hext::NthChildMatch p(0, pos);
      auto res = p.matches(node);
      EXPECT_TRUE(res.first);
    }
    {
      hext::NthChildMatch p(
        0,
        rev_pos,
        GUMBO_TAG_UNKNOWN,
        hext::NthChildMatch::OffsetOf::Back
      );
      auto res = p.matches(node);
      EXPECT_TRUE(res.first);
    }
    {
      hext::NthChildMatch p(
        0,
        tag_pos,
        tag(node)
      );
      auto res = p.matches(node);
      EXPECT_TRUE(res.first);
    }
    {
      hext::NthChildMatch p(
        0,
        tag_rev_pos,
        tag(node),
        hext::NthChildMatch::OffsetOf::Back
      );
      auto res = p.matches(node);
      EXPECT_TRUE(res.first);
    }
  }
}

TEST(Pattern_NthChildMatch, MatchesWithStepAndShift)
{
  using helper::attr_value;
  using helper::tag;

  helper::Html h(html);
  const GumboNode * body = h.body();
  ASSERT_NE(body, nullptr);
  ASSERT_EQ(body->type, GUMBO_NODE_ELEMENT);

  const GumboVector& children = body->v.element.children;
  ASSERT_EQ(children.length, 15);

  for(unsigned int i = 0; i < children.length; ++i)
  {
    auto node = static_cast<const GumboNode *>(children.data[i]);
    ASSERT_EQ(node->type, GUMBO_NODE_ELEMENT);

    int pos = std::stoi(attr_value(node, "pos"));
    int rev_pos = std::stoi(attr_value(node, "rev-pos"));
    int tag_pos = std::stoi(attr_value(node, "tag-pos"));
    int tag_rev_pos = std::stoi(attr_value(node, "tag-rev-pos"));

    for(int step = 1; step < 21; ++step)
    {
      for(int shift = 1; shift < 21; ++shift)
      {
        {
          hext::NthChildMatch p(step, shift);
          auto res = p.matches(node);
          EXPECT_EQ(pos % step == shift % step, res.first);
        }

        {
          hext::NthChildMatch p(
            step,
            shift,
            GUMBO_TAG_UNKNOWN,
            hext::NthChildMatch::OffsetOf::Back
          );
          auto res = p.matches(node);
          EXPECT_EQ(rev_pos % step == shift % step, res.first);
        }

        {
          hext::NthChildMatch p(step, shift, tag(node));
          auto res = p.matches(node);
          EXPECT_EQ(tag_pos % step == shift % step, res.first);
        }

        {
          hext::NthChildMatch p(
            step,
            shift,
            tag(node),
            hext::NthChildMatch::OffsetOf::Back
          );
          auto res = p.matches(node);
          EXPECT_EQ(tag_rev_pos % step == shift % step, res.first);
        }
      }
    }
  }
}


} // namespace

