#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ios>

#include "hext/parser.h"
#include "hext/html.h"
#include "hext/file.h"
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
    const std::string bf_hext = hext::read_file_or_throw(po.get("hext-file"));
    const auto rules = hext::parser::parse_range(
      bf_hext.c_str(),
      bf_hext.c_str() + bf_hext.size()
    );

    if( po.contains("print") )
    {
      for(const auto& r : rules)
        r.print();
      return EXIT_SUCCESS;
    }

    if( po.contains("lint") )
      return EXIT_SUCCESS;

    const std::string bf_html = hext::read_file_or_throw(po.get("html-file"));
    const hext::html html(bf_html.c_str(), bf_html.size());

    for(const auto& rule : rules)
    {
      std::unique_ptr<hext::match_tree> mt = html.extract(rule);
      assert(mt != nullptr);

      if( !po.contains("keep-invalid") )
        mt->filter();

      if( po.contains("print-debug") )
      {
        rule.print(std::cout, 0, true);
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
  catch( const hext::file_error& e )
  {
    std::cerr << argv[0] << ": Error: " << e.what() << "\n";
    return EXIT_FAILURE;
  }
  catch( const hext::parser::parse_error& e )
  {
    std::cerr << argv[0] << ": Error in "
              << po.get("hext-file") << ": "
              << e.what() << "\n";
    return EXIT_FAILURE;
  }
  catch( const hext::lexer::lex_error& e )
  {
    std::cerr << argv[0] << ": Error in "
              << po.get("hext-file") << ": "
              << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

