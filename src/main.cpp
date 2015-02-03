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

  if( !po.validate_or_print_error(std::cerr) )
    return EXIT_FAILURE;

  if( argc < 2 || po.contains("help") )
  {
    po.print(argv[0], std::cout);
    return EXIT_SUCCESS;
  }

  try
  {
    auto rules = hext::parser::parse_file(po.get("hext-file"));

    if( po.contains("print") )
    {
      for(const auto& r : rules)
        r.print();
      return EXIT_SUCCESS;
    }

    if( po.contains("lint") )
      return EXIT_SUCCESS;

    hext::matcher m(po.get("html-file"));

    for(const auto& r : rules)
    {
      std::unique_ptr<hext::match_tree> mt = m.match(r);
      assert(mt != nullptr);

      if( !po.contains("no-filter") )
        mt->filter();

      if( po.contains("print-debug") )
      {
        r.print(std::cout, 0, true);
      }
      else if( po.contains("mt-graph") )
      {
        mt->print_dot();
      }
      else
      {
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

