#include <cassert>
#include <cstdlib>
#include <iostream>
#include <ios>

#include "hext/parser.h"
#include "hext/matcher.h"
#include "hext/program-options.h"


int main(int argc, const char ** argv)
{
  std::ios_base::sync_with_stdio(false);

  hext::program_options po(argc, argv);

  if( po.contains("help") )
  {
    po.print(argv[0], std::cout);
    return EXIT_SUCCESS;
  }

  if( !po.validate_or_print_error(std::cerr) )
    return EXIT_FAILURE;

  try
  {
    auto rules = hext::parser::parse_file(po.get("hext-file"));
    hext::matcher m(po.get("html-file"));

    for(const auto& r : rules)
    {
      std::fstream g(
        "auto.graph.dot",
        std::fstream::out|std::fstream::trunc
      );
      std::fstream gf(
        "auto.graph.filtered.dot",
        std::fstream::out|std::fstream::trunc
      );

      std::unique_ptr<hext::match_tree> mt = m.match(r);
      assert(mt != nullptr);

      if( po.contains("mt-graph") )
      {
        mt->print_dot(g); // debug
        mt->filter();
        mt->print_dot(gf); // debug
        mt->print_dot();
      }
      else if( po.contains("unfiltered-mt-graph") )
      {
        mt->print_dot();
      }
      else
      {
        mt->filter();
        mt->print_json();
      }
    }
  }
  catch( std::ios_base::failure& e )
  {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

