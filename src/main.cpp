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
    std::ifstream hext_file(po.get("hext-file"), std::ios::in | std::ios::binary);
    if( !hext_file )
    {
      std::cerr << "failed opening hext-file\n";
      return EXIT_FAILURE;
    }
    const std::string hext_buffer = hext::read_file(hext_file);
    hext_file.close();
    const auto rules = hext::parser::parse_range(
      hext_buffer.c_str(),
      hext_buffer.c_str() + hext_buffer.size()
    );

    if( po.contains("print") )
    {
      for(const auto& r : rules)
        r.print();
      return EXIT_SUCCESS;
    }

    if( po.contains("lint") )
      return EXIT_SUCCESS;

    std::ifstream html_file(po.get("html-file"), std::ios::in | std::ios::binary);
    if( !html_file )
    {
      std::cerr << "failed opening html-file\n";
      return EXIT_FAILURE;
    }
    const std::string html_buffer = hext::read_file(html_file);
    html_file.close();
    const hext::html html(html_buffer.c_str(), html_buffer.size());

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
  catch( std::ios_base::failure& e )
  {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

