#include "hext/json.h"
#include "hext/file.h"
#include "hext/program-options.h"
#include "hext/hext.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <ios>


int main(int argc, const char ** argv)
{
  std::ios_base::sync_with_stdio(false);

  hext::ProgramOptions po;

  try
  {
    po.store_and_validate_or_throw(argc, argv);

    if( po.contains("help") )
    {
      po.print(argv[0], std::cout);
      return EXIT_SUCCESS;
    }

    std::string hext_str = hext::ReadFileOrThrow(po.get("hext-file"));
    hext::Hext extractor(hext_str);

    if( po.contains("lint") )
      return EXIT_SUCCESS;

    hext::Option flags = hext::Option::Default;
    if( po.contains("keep-invalid") )
      flags |= hext::Option::KeepInvalid;

    std::string html = hext::ReadFileOrThrow(po.get("html-file"));
    hext::Result result = extractor.extract(html, flags);

    for(const auto& v : result)
      hext::PrintJson(v);
  }
  catch( const boost::program_options::error& e )
  {
    std::cerr << argv[0] << ": Argument error: " << e.what() << "\n";
    return EXIT_FAILURE;
  }
  catch( const hext::FileError& e )
  {
    std::cerr << argv[0] << ": Error: " << e.what() << "\n";
    return EXIT_FAILURE;
  }
  catch( const hext::ParseError& e )
  {
    std::cerr << argv[0] << ": Error in "
              << po.get("hext-file") << ": "
              << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

