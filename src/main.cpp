#include <cstdlib>
#include <iostream>
#include <ios>

#include "hext/parser.h"
#include "hext/print.h"

int main(int argc, char ** argv)
{
  // todo: boost::program_options
  if( argc < 2 )
  {
    std::cout << "Usage: " << argv[0] << " [rules.hext]" << std::endl;
    return EXIT_SUCCESS;
  }
  
  try
  {
    auto rules = hext::parser::parse_file(argv[1]);
    for(const auto& r : rules)
    {
      print_rule(r);
    }
  }
  catch( std::ios_base::failure& e )
  {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

