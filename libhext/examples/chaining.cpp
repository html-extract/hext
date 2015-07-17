#include <cstdlib>
#include <cstring>
#include <iostream>

#include "hext/Hext.h"

int main()
{
  using namespace hext;

  Rule rdiv;
  rdiv.set_tag(HtmlTag::DIV)
  // <div>
      .add_match<AttributeCountMatch>(0)
      .take_child(std::move(
  //    <ul>
        Rule(HtmlTag::UL)
  //      :attribute-count(0)
          .add_match<AttributeCountMatch>(0)
          .take_child(std::move(
  //        <li>
            Rule(HtmlTag::LI)
              .take_child(std::move(
  //            <a>
                Rule(HtmlTag::A)
  //               href
                  .add_match<AttributeMatch>("href")
  //               href={link}
                  .add_capture<AttributeCapture>("href", "link")
              ))
          ))
      ))
  ;

  const char * input = R"input(
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
  )input";

  Html html(input, std::strlen(input));
  auto result_tree = rdiv.extract(html.root());
  auto v = result_tree->flatten();

  for(const auto& m : v)
    for(const auto& p : m)
      std::cout << p.first << ": " << p.second << "\n";

  return EXIT_SUCCESS;
}

