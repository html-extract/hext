#include "hext/Parser.h"


namespace {


TEST(Parser, Empty)
{
  const char * begin = "";
  hext::Parser p(begin, begin);
  std::vector<hext::Rule> v = p.parse();
  EXPECT_TRUE(v.empty());
}

TEST(Parser, Throws)
{
  const char * strs[] = {
    "<unknown_html_tag>",
    "<:unknown_trait>",
    "<:nth-child()>",
    "<:nth-child(n)>",
    " <>",
    "<0>",
    "<0a>",
    "<a0>",
    "<a!>",
    "<1a?>",
    "<1a ?>",
    "<'a>",
    "a>",
    "<a",
    "< a=>",
    "< a=\">",
    "< a=/>",
    "< a={>",
    "< @a>",
    "< @a=/a>",
    "<>\n <>\n"
  };

  for(const char * str : strs)
  {
    hext::Parser p(str, str + strlen(str));
    EXPECT_THROW(p.parse(), hext::ParseError) << "with hext: " << str;
  }
}

TEST(Parser, Comment)
{
  const char * strs[] = {
    "# single comment\n",
    "# multiple comments\n# multiple comments\n# multiple comments\n",
    "# a comment and\n<a>\n# and a comment\n",
    "# a comment and\n<a>\n # and a comment\n",
    "# a comment and\n<a>\n  # and a comment\n",
    "<a>\n# and a comment\n",
    "#a comment and\n<a>\n"
  };

  for(const char * str : strs)
  {
    hext::Parser p(str, str + strlen(str));
    EXPECT_NO_THROW(p.parse()) << "with hext: " << str;
  }
}

TEST(Parser, Patterns)
{
  const char * strs[] = {
    "<a href>",
    "<a href=\"http...\">",
    "<a href=/http.../>",
    "<a href=/http:\\/\\//>",
    "<a href={href}>",
    "<a @text={text}>",
    "<a @text={text/regex/}>",
    "<a @text={text/http:\\/\\//}>",
    "<a @text=\"text\">\n",
    "<a @text=/text/>",
    "<a @text=/http:\\/\\//>"
  };

  for(const char * str : strs)
  {
    hext::Parser p(str, str + strlen(str));
    std::vector<hext::Rule> v = p.parse();
    EXPECT_EQ(v.size(), 1);
  }
}

TEST(Parser, RepeatedParse)
{
  const char * hxt = "<?a href={href}>\n  <a bla=/test/>";
  hext::Parser p(hxt, hxt + strlen(hxt));

  for(int i = 0; i < 5; ++i)
  {
    std::vector<hext::Rule> v = p.parse();
    ASSERT_EQ(v.size(), 1);
    EXPECT_TRUE(v.front().optional());
    ASSERT_EQ(v.front().children().size(), 1);
    EXPECT_FALSE(v.front().children().front().optional());
  }
}


} // namespace

