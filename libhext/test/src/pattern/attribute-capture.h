#include "hext/pattern/AttributeCapture.h"

#include "test-helper/html.h"


namespace {


TEST(Pattern_AttributeCapture, Captures)
{
  helper::Html h("<html><head></head><body class='class-value'></body></html>");
  hext::AttributeCapture p("result", "class");
  auto pair = p.capture(h.body());
  EXPECT_EQ(pair.first, "result");
  EXPECT_EQ(pair.second, "class-value");
}

TEST(Pattern_AttributeCapture, CapturesWithRegex)
{
  helper::Html h("<html><head></head><body class='class-value'></body></html>");
  hext::AttributeCapture p("result", "class", boost::regex("class-(.*)"));
  auto pair = p.capture(h.body());
  EXPECT_EQ(pair.first, "result");
  EXPECT_EQ(pair.second, "value");
}

TEST(Pattern_AttributeCapture, CapturesAllWithNoCapRegex)
{
  helper::Html h("<html><head></head><body class='class-value'></body></html>");
  hext::AttributeCapture p("result", "class", boost::regex(".*"));
  auto pair = p.capture(h.body());
  EXPECT_EQ(pair.first, "result");
  EXPECT_EQ(pair.second, "class-value");
}

TEST(Pattern_AttributeCapture, MissingAttrReturnsEmpty)
{
  helper::Html h("<html><head></head><body></body></html>");
  hext::AttributeCapture p("result", "class");
  auto pair = p.capture(h.body());
  EXPECT_EQ(pair.first, "result");
  EXPECT_EQ(pair.second, "");
}


} // namespace

