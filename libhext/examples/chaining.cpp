// Copyright 2015 Thomas Trapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cstdlib>
#include <iostream>

#include "hext/Hext.h"

int main()
{
  using namespace hext;

  Rule rdiv;
  rdiv.set_tag(HtmlTag::DIV)
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

  auto result = rdiv.extract(html);

  for(const auto& g : result)
    for(const auto& p : g)
      std::cout << p.first << ": " << p.second << "\n";

  return EXIT_SUCCESS;
}

