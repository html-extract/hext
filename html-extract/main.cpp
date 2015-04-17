#include "htmlext/Json.h"
#include "htmlext/File.h"
#include "htmlext/ProgramOptions.h"
#include "htmlext/Version.h"
#include "hext/Hext.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <ios>


int main(int argc, const char ** argv)
{
  std::ios_base::sync_with_stdio(false);

  htmlext::ProgramOptions po;

  try
  {
    po.store_and_validate_or_throw(argc, argv);

    if( po.contains("help") )
    {
      po.print(argv[0], std::cout);
      return EXIT_SUCCESS;
    }

    if( po.contains("version") )
    {
      htmlext::PrintVersion(std::cout);
      return EXIT_SUCCESS;
    }

    hext::Option flags = hext::DefaultOption;
    if( po.contains("keep-incomplete") )
      flags &= ~hext::Option::RemoveIncomplete;
    if( po.contains("no-auto-any-descendant") )
      flags &= ~hext::Option::ForceTopRuleAnyDesc;
    if( po.contains("cap-attrib-optional") )
      flags &= ~hext::Option::CapAttribMustExist;
    if( po.contains("no-merge-results") )
      flags &= ~hext::Option::InterleaveResults;

    std::string hext_str = htmlext::ReadFileOrThrow(po.get("hext"));
    hext::Hext extractor(hext_str, flags);

    if( po.contains("lint") )
      return EXIT_SUCCESS;

    std::vector<std::string> html_input = po.get_html_input();
    for(const auto& file : html_input)
    {
      std::string html = htmlext::ReadFileOrThrow(file);
      hext::Result result = extractor.extract(html);

      for(const auto& v : result)
        htmlext::PrintJson(v);
    }
  }
  catch( const boost::program_options::error& e )
  {
    std::cerr << argv[0] << ": Argument error: " << e.what() << "\n";
    return EXIT_FAILURE;
  }
  catch( const htmlext::FileError& e )
  {
    std::cerr << argv[0] << ": Error: " << e.what() << "\n";
    return EXIT_FAILURE;
  }
  catch( const hext::ParseError& e )
  {
    std::cerr << argv[0] << ": Error in "
              << ( po.contains("hext") ? po.get("hext") : "unknown" )
              << ": " << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

