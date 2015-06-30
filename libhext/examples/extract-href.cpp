#include "hext/Hext.h"

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>


int main()
{
  std::ios_base::sync_with_stdio(false);
  using namespace hext;

  Rule a_href(GUMBO_TAG_A);
  a_href.add_match<AttributeMatch>("href")
        .add_match<AttributeMatch>("href",
          MakeUnique<test::Negate>(
            MakeUnique<test::BeginsWith>("javascript:")
          )
        )
        .add_match<AttributeMatch>("href",
          MakeUnique<test::Negate>(
            MakeUnique<test::BeginsWith>("#")
          )
        )
        .add_capture<AttributeCapture>("href", "link");

  std::stringstream in_sstr;
  {
    std::ifstream in("/dev/stdin");
    in_sstr << in.rdbuf();
  }

  Html html(in_sstr.str());
  auto result_tree = a_href.extract(html.root());
  auto flat_result = result_tree->flatten();

  for(const auto& m : flat_result)
    for(const auto& p : m)
      std::cout << p.second << "\n";

  return EXIT_SUCCESS;
}

