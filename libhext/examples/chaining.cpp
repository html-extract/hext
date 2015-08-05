#include <cstdlib>
#include <cstring>
#include <iostream>

#include "hext/Hext.h"

int main()
{
  using namespace hext;

  Rule rdiv;
  rdiv.set_tag(HtmlTag::DIV)
      .set_any_descendant(true)
      .append_match<AttributeCountMatch>(0)
      .append_child(
        Rule(HtmlTag::UL)
          .append_match<AttributeCountMatch>(0)
          .append_child(
            Rule(HtmlTag::LI)
              .append_child(
                Rule(HtmlTag::A)
                  .append_match<AttributeMatch>("href")
                  .append_capture<AttributeCapture>("href", "link"))));

  Html html(R"input(
    <html>
      <head></head>
      <body>
        <div>
          <ul attribute>
            <li><a href="nope1"></a></li>
            <li><a href="nope2"></a></li>
          </ul>
        </div>
        <div>
          <ul>
            <li><a href="result1"></a></li>
            <li><a href="result2"></a></li>
            <li><a href="result3"></a></li>
            <li><a href="result4"></a></li>
            <li><a href="result5"></a></li>
            <li><a href="result6"></a></li>
            <li><a href="result7"></a></li>
            <li><a nope3></a></li>
          </ul>
          <div>
            <div>
              <a href="nope4"></a>
            </div>
          </div>
        </div>
      </body>
    </html>
  )input");

  auto result = rdiv.extract(html.root());

  for(const auto& g : result)
    for(const auto& p : g)
      std::cout << p.first << ": " << p.second << "\n";

  return EXIT_SUCCESS;
}

