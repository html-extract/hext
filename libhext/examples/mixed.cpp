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

// enable asserts in release build
#undef NDEBUG
#include <cassert>

#include <cstdlib>
#include <iostream>
#include <string>

#include "hext/Hext.h"


int main()
{
  using namespace hext;

  int match_counter = 0;
  CaptureFunction count_captures = [&match_counter]
    (const GumboNode *) -> std::string
    {
      return std::to_string(++match_counter);
    };

  Rule anchor(HtmlTag::A);
  anchor.append_match<AttributeMatch>("href")
        .append_capture<AttributeCapture>(/* attr_name:    */ "href",
                                          /* capture name: */ "href");

  try
  {
    auto img = ParseHext("<img src:img /><p @text:par />");

    auto par = img.next();
    assert(par);

    par->append_child(ParseHext("<?span @text:span />"));
    assert(par->child());

    anchor.append_child(std::move(img));
  }
  catch( const hext::SyntaxError& e )
  {
    std::cerr << "Syntax error: " << e.what() << "\n";
    return EXIT_FAILURE;
  }

  // Rule anchor is now equivalent to this hext snippet:
  // <a href:href>
  //   <img src:img />
  //   <p @text:par>
  //     <?span @text:span />
  //   </p>
  // </a>

  {
    auto first_child = anchor.child(); // <img/>
    assert(first_child);

    auto second_child = first_child->next(); // <p>
    assert(second_child);

    auto grand_child = second_child->child(); // <?span/>
    assert(grand_child);

    // add a lambda that is called for every matching <span/>
    grand_child->append_capture<FunctionCapture>(
        /* CaptureFunction: */ count_captures,
        /* capture name:    */ "number");
  }

  Html html(
    "<a href='href1'><img src='src1' /><p>1 <span>a</span></p></a>"
    "<a href='href2'><img src='src2' /><p>2 <span>b</span></p></a>"
    "<a href='href3'><img src='src3' /><p>3 <code>c</code></p></a>"
    "<a href='href4'><img src='src4' /><p>4 <span>d</span></p></a>"
    "<a href='href5'><img src='src5' /><p>5 <span>e</span></p></a>");

  auto result = anchor.extract(html);
  for(const auto& group : result)
  {
    for(const auto& pair : group)
      std::cout << pair.first << ": " << pair.second << "\n";

    std::cout << "\n";
  }

  return EXIT_SUCCESS;
}

