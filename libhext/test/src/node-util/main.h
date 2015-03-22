#include "hext/NodeUtil.h"
#include "test-helper/html.h"
#include "test-helper/node.h"

#include <string>

#include <gumbo.h>


namespace {


TEST(Node_GetNodePositionWithinParent_AndReverse, Position)
{
  using helper::attr_value;
  using helper::tag;

  // Test html with expected node position as attribute 'pos'.
  const char * pos_html = R"(
      This
    <div  pos="1" pos-div="1">is</div>
    <span pos="2" pos-span="1">a</span>
      string
    <div  pos="3" pos-div="2">all</div>
    <span pos="4" pos-span="2">over</span>
      the
      place
  )";

  helper::Html h(pos_html);
  const GumboNode * body = h.body();

  const GumboVector& body_children = body->v.element.children;
  ASSERT_GT(body_children.length, 1);

  // Check for each child of type element, that GetNodePositionWithinParent
  // returns the same value, as the attribute "pos".
  for(unsigned int i = 0; i < body_children.length; ++i)
  {
    auto node = static_cast<const GumboNode *>(body_children.data[i]);
    if( node->type == GUMBO_NODE_ELEMENT )
    {
      int pos = std::stoi(attr_value(node, "pos"));
      EXPECT_EQ(pos,
          hext::GetNodePositionWithinParent(node));
      EXPECT_EQ(5 - pos,
          hext::GetNodePositionWithinParentReverse(node));

      int tag_pos = std::stoi(
        attr_value(
          node,
          ( tag(node) == GUMBO_TAG_SPAN ? "pos-span" : "pos-div" )
        )
      );

      EXPECT_EQ(tag_pos,
        hext::GetNodePositionWithinParent(node, tag(node)));
      EXPECT_EQ(3 - tag_pos,
        hext::GetNodePositionWithinParentReverse(node, tag(node)));
    }
  }
}

TEST(Node_GetNodeChildCount, Nullptr)
{
  EXPECT_EQ(hext::GetNodeChildCount(nullptr), 0);
}

TEST(Node_GetNodeChildCount, ChildCount)
{
  const char * html = R"(
      This
    <div>is</div>
    <span>a</span>
      string
    <div>all</div>
    <span>over</span>
      the
      place
  )";

  helper::Html h(html);
  const GumboNode * body = h.body();
  EXPECT_EQ(hext::GetNodeChildCount(body), 4);
}

TEST(Node_GetNodeText, NiceTextAndRawText)
{
  const char * html = R"html(
<html><head></head><body>
 
   This is  <span> a</span>badly 

formatted<div><div>html</div>document.

</div>
</body></html>
)html";

  helper::Html h(html);
  const GumboNode * body = h.body();

  const char * expected = "This is a badly formatted html document.";
  EXPECT_EQ(hext::GetNodeText(body), expected);

  const char * expected_raw = R"html( 
 
   This is     a badly 

formatted   html document.

)html";
  EXPECT_EQ(hext::GetNodeRawText(body), expected_raw);
}

TEST(Node_GetNodeInnerHtml, Empty)
{
  const char * html = "<html><head></head><body>"
    "</body></html>";

  helper::Html h(html);
  const GumboNode * body = h.body();

  EXPECT_EQ(hext::GetNodeInnerHtml(body), "");
}

TEST(Node_GetNodeInnerHtml, InnerHtml)
{
  std::string html = "<html><head></head><body>";
  const char * inner = "<div><div> --- text --- </div>"
    "<div> --- stuff --- </div></div>";
  html.append(inner);
  html.append("</body></html>");

  helper::Html h(html.c_str());
  const GumboNode * body = h.body();

  EXPECT_EQ(hext::GetNodeInnerHtml(body), inner);
}

TEST(Node_GetNodeInnerHtml, BrokenHtml)
{
  std::string html = "<html><head></head><body>";
  const char * inner = "<div><div> --- text --- </div>"
    "<div> --- stuff --- </div><a>"; // missing </div>, stray <a>
  html.append(inner);
  html.append("</body></html>");

  helper::Html h(html.c_str());
  const GumboNode * body = h.body();

  EXPECT_EQ(hext::GetNodeInnerHtml(body), inner);
}

TEST(Node_All, Nullptr)
{
  const GumboNode * nullnode = nullptr;
  EXPECT_EQ(hext::GetNodePositionWithinParent(nullnode), 0);
  EXPECT_EQ(hext::GetNodeText(nullnode), "");
  EXPECT_EQ(hext::GetNodeRawText(nullnode), "");
  EXPECT_EQ(hext::GetNodeInnerHtml(nullnode), "");
}


} // namespace

