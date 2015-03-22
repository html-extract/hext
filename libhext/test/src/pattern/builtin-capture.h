#include "hext/pattern/BuiltinCapture.h"

#include "test-helper/html.h"


namespace {


TEST(Pattern_BuiltinCapture, Captures)
{
  helper::Html h("<html><head></head><body class='class-value'>\
    Inner Text\
    </body></html>");
  hext::BuiltinCapture p("result", hext::GetNodeText);
  auto pair = p.capture(h.body());
  EXPECT_EQ(pair.first, "result");
  EXPECT_EQ(pair.second, "Inner Text");
}

TEST(Pattern_BuiltinCapture, CapturesWithRegex)
{
  helper::Html h("<html><head></head><body class='class-value'>\
    Inner Text\
    </body></html>");
  hext::BuiltinCapture p(
    "result",
    hext::GetNodeText,
    boost::regex("Inner (.*)")
  );
  auto pair = p.capture(h.body());
  EXPECT_EQ(pair.first, "result");
  EXPECT_EQ(pair.second, "Text");
}

TEST(Pattern_BuiltinCapture, CapturesAllWithNoCapRegex)
{
  helper::Html h("<html><head></head><body class='class-value'>\
    Inner Text\
    </body></html>");
  hext::BuiltinCapture p(
    "result",
    hext::GetNodeText,
    boost::regex(".*")
  );
  auto pair = p.capture(h.body());
  EXPECT_EQ(pair.first, "result");
  EXPECT_EQ(pair.second, "Inner Text");
}


} // namespace

