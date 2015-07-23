
TEST(Builtins_TextBuiltin, ExtractsText)
{
  {
    THtml h(R"html(
<html><head></head><body>

   This is  <span> a</span><span> b</span>adly
f<span>ormatte</span>d<div><div>html</div>doc<a>ume</a>nt<span></span>.
<div><span></span>

</div>
</body></html>
  )html");
    EXPECT_EQ(TextBuiltin(h.root()), "This is a badly formatted html document.");
  }

  {
    THtml h("<div></div>");
    EXPECT_EQ(TextBuiltin(h.root()), "");
  }

  {
    THtml h(".");
    EXPECT_EQ(TextBuiltin(h.root()), ".");
  }
}

