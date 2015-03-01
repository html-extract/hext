#include "hext/parser.h"


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
    "<unknown_html_tag",
    " <",
    "<0",
    "<0a",
    "<a0",
    "<a!",
    "<1a?",
    "<1a ?",
    "<'a",
    "a",
    "< a=",
    "< a=\"",
    "< a=/",
    "< a={",
    "< @a",
    "< @a=/a",
    "<\n <\n"
  };

  for(const char * str : strs)
  {
    hext::Parser p(str, str + strlen(str));
    EXPECT_THROW(p.parse(), hext::ParseError);
  }
}

TEST(Parser, Comment)
{
  const char * strs[] = {
    "# single comment\n",
    "# multiple comments\n# multiple comments\n# multiple comments\n",
    "# a comment and\n<a rule\n# and a comment\n",
    "# a comment and\n<a rule\n # and a comment\n",
    "# a comment and\n<a rule\n  # and a comment\n",
    "<a rule\n# and a comment\n",
    "#a comment and\n<a rule\n"
  };

  for(const char * str : strs)
  {
    hext::Parser p(str, str + strlen(str));
    EXPECT_NO_THROW(p.parse());
  }
}

TEST(Parser, Patterns)
{
  const char * strs[] = {
    "<a href\n",
    "<a href=\"http...\"\n",
    "<a href=/http.../\n",
    "<a href=/http:\\/\\//\n",
    "<a href={href}\n",
    "<a @text={text}\n",
    "<a @text={text/regex/}\n",
    "<a @text={text/http:\\/\\//}\n",
    "<a @text=\"text\"\n",
    "<a @text=/text/\n",
    "<a @text=/http:\\/\\//\n"
  };

  for(const char * str : strs)
  {
    hext::Parser p(str, str + strlen(str));
    std::vector<hext::Rule> v = p.parse();
    EXPECT_EQ(v.size(), 1);
  }
}


} // namespace

