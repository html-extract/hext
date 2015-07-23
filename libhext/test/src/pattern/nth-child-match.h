
namespace {


const char * nth_table_html =
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


TEST(Pattern_NthChildMatch, Front)
{
  THtml h(nth_table_html);
  auto front = NthChildMatch::Front;

  EXPECT_FALSE(NthChildMatch(2, 0).matches(h.body_child(1)));
  EXPECT_FALSE(NthChildMatch(2, 0).matches(h.body_child(15)));
  EXPECT_TRUE( NthChildMatch(2, 0).matches(h.body_child(2)));
  EXPECT_TRUE( NthChildMatch(2, 0).matches(h.body_child(14)));

  EXPECT_FALSE(NthChildMatch(2, 1).matches(h.body_child(2)));
  EXPECT_FALSE(NthChildMatch(2, 1).matches(h.body_child(14)));
  EXPECT_TRUE( NthChildMatch(2, 1).matches(h.body_child(1)));
  EXPECT_TRUE( NthChildMatch(2, 1).matches(h.body_child(15)));

  EXPECT_FALSE(NthChildMatch(-2, 15).matches(h.body_child(2)));
  EXPECT_FALSE(NthChildMatch(-2, 15).matches(h.body_child(14)));
  EXPECT_TRUE( NthChildMatch(-2, 15).matches(h.body_child(1)));
  EXPECT_TRUE( NthChildMatch(-2, 15).matches(h.body_child(15)));

  EXPECT_FALSE(NthChildMatch(2, 1, front, HtmlTag::SPAN).matches(h.body_child(1)));
  EXPECT_FALSE(NthChildMatch(2, 1, front, HtmlTag::SPAN).matches(h.body_child(15)));
  EXPECT_FALSE(NthChildMatch(2, 1, front, HtmlTag::SPAN).matches(h.body_child(9)));
  EXPECT_TRUE( NthChildMatch(2, 1, front, HtmlTag::SPAN).matches(h.body_child(4)));

  EXPECT_FALSE(NthChildMatch(0, 3).matches(h.body_child(6)));
  EXPECT_TRUE( NthChildMatch(0, 3).matches(h.body_child(3)));
}

TEST(Pattern_NthChildMatch, Back)
{
  THtml h(nth_table_html);
  auto back = NthChildMatch::Back;

  EXPECT_FALSE(NthChildMatch(2, 0, back).matches(h.body_child(1)));
  EXPECT_FALSE(NthChildMatch(2, 0, back).matches(h.body_child(15)));
  EXPECT_TRUE( NthChildMatch(2, 0, back).matches(h.body_child(2)));
  EXPECT_TRUE( NthChildMatch(2, 0, back).matches(h.body_child(14)));

  EXPECT_FALSE(NthChildMatch(2, 1, back).matches(h.body_child(2)));
  EXPECT_FALSE(NthChildMatch(2, 1, back).matches(h.body_child(14)));
  EXPECT_TRUE( NthChildMatch(2, 1, back).matches(h.body_child(1)));
  EXPECT_TRUE( NthChildMatch(2, 1, back).matches(h.body_child(15)));

  EXPECT_FALSE(NthChildMatch(-2, 15, back).matches(h.body_child(2)));
  EXPECT_FALSE(NthChildMatch(-2, 15, back).matches(h.body_child(14)));
  EXPECT_TRUE( NthChildMatch(-2, 15, back).matches(h.body_child(1)));
  EXPECT_TRUE( NthChildMatch(-2, 15, back).matches(h.body_child(15)));

  EXPECT_FALSE(NthChildMatch(2, 1, back, HtmlTag::SPAN).matches(h.body_child(1)));
  EXPECT_FALSE(NthChildMatch(2, 1, back, HtmlTag::SPAN).matches(h.body_child(15)));
  EXPECT_FALSE(NthChildMatch(2, 1, back, HtmlTag::SPAN).matches(h.body_child(4)));
  EXPECT_TRUE( NthChildMatch(2, 1, back, HtmlTag::SPAN).matches(h.body_child(9)));

  EXPECT_FALSE(NthChildMatch(0, 3, back).matches(h.body_child(12)));
  EXPECT_TRUE( NthChildMatch(0, 3, back).matches(h.body_child(13)));
}


} // namespace

