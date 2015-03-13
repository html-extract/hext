#include "hext/node-util.h"
#include "test-helper/html.h"

#include <string>

#include <gumbo.h>


namespace {


TEST(Node_GetNodePositionWithinParent, Position)
{
  // Test html with expected node position as attribute 'pos'.
  const char * pos_html = R"html(
<html><head></head><body>
  This
  <div pos="1">is</div>
  <div pos="2">a</div>
  string
  <div pos="3">all</div>
  <div pos="4">over</div>
  the
  place
</body></html>
)html";

  helper::Html h(pos_html);
  const GumboNode * body = h.body();

  const GumboVector& body_children = body->v.element.children;
  ASSERT_GT(body_children.length, 1);

  // Check for each child of type element, that GetNodePositionWithinParent
  // returns the same value, as the attribute "pos".
  for(unsigned int i = 0; i < body_children.length; ++i)
  {
    const GumboNode * node = static_cast<const GumboNode *>(
      body_children.data[i]
    );
    if( node->type == GUMBO_NODE_ELEMENT )
    {
      const GumboAttribute * g_attr = gumbo_get_attribute(
        &node->v.element.attributes,
        "pos"
      );
      ASSERT_TRUE(g_attr);
      ASSERT_TRUE(g_attr->value);
      int expected = std::stoi(g_attr->value);
      EXPECT_EQ(expected, hext::GetNodePositionWithinParent(node));
    }
  }
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
  const char * html = "<html><head></head><body>";
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

