#include <cstdlib>
#include <iostream>
#include <ios>

#include "hext/parser.h"
#include "hext/matcher.h"
#include "hext/print.h"


int main(int argc, char ** argv)
{
  // todo: boost::program_options
  if( argc < 3 )
  {
    std::cout << "Usage: " << argv[0]
              << " [rules.hext] [target.html]" << std::endl;
    return EXIT_SUCCESS;
  }

  try
  {
    auto rules = hext::parser::parse_file(argv[1]);
    hext::matcher m(argv[2]);

    for(const auto& r : rules)
    {
      hext::print_rule(r);
      hext::match_tree mt = m.match(r);
      hext::print_match_tree(mt);
    }
  }
  catch( std::ios_base::failure& e )
  {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

