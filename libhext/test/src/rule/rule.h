#include <memory>
#include <utility>

TEST(Rule_Rule, ExampleFromDocumentation)
{
  Rule anchor(HtmlTag::A);
  anchor.append_match<AttributeMatch>("href")
        .append_capture<AttributeCapture>("href", "link");
  {
    Rule img(HtmlTag::IMG);
    img.append_capture<AttributeCapture>("src", "img");
    anchor.append_child(std::move(img));
  }

  // <a href={link}><img src={img}/></a>
  Html html(
    "<html><body>"
      "<div><a href='/bob'>  <img src='bob.jpg'/>  </a></div>"
      "<div><a href='/alice'><img src='alice.jpg'/></a></div>"
      "<div><a href='/carol'><img src='carol.jpg'/></a></div>"
    "</body></html>");

  Result result = anchor.extract(html);

  Result expected = {
    {
      {"link", "/bob"},
      {"img", "bob.jpg"}
    },
    {
      {"link", "/alice"},
      {"img", "alice.jpg"}
    },
    {
      {"link", "/carol"},
      {"img", "carol.jpg"}
    }
  };

  EXPECT_EQ(result, expected);
}

TEST(Rule_Rule, SettersGetters)
{
  Rule r;
  EXPECT_EQ(r.get_tag(), HtmlTag::ANY);
  EXPECT_EQ(r.is_optional(), false);

  r.set_tag(HtmlTag::SPAN);
  r.set_optional(true);
  EXPECT_EQ(r.get_tag(), HtmlTag::SPAN);
  EXPECT_EQ(r.is_optional(), true);
}

