#include <string>

TEST(Builtins_InnerHtmlBuiltin, ExtractsHtml)
{
  std::string html = "<html><head></head><body>";
  const char * inner = "<div><div> --- text --- </div>"
    "<div> --- stuff --- </div></div>";
  html.append(inner);
  html.append("</body></html>");

  THtml h(html.c_str());
  EXPECT_EQ(InnerHtmlBuiltin(h.body()), inner);
}

TEST(Builtins_InnerHtmlBuiltin, ExtractsBrokenHtmlUntouched)
{
  std::string html = "<html><head></head><body>";
  const char * inner = "<div><div> --- text --- </div>"
    "<div> --- stuff --- </div><a>"; // missing </div>, stray <a>
  html.append(inner);
  html.append("</body></html>");

  THtml h(html.c_str());
  EXPECT_EQ(InnerHtmlBuiltin(h.body()), inner);
}

