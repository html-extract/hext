#include "hext/Hext.h"

#include "htmlext/File.h"
#include "htmlext/Json.h"
#include "htmlext/PrintDot.h"
#include "htmlext/ProgramOptions.h"
#include "htmlext/Version.h"

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

    if( po.contains("print-html-dot") )
    {
      std::string file = po.get("print-html-dot");
      std::string html = htmlext::ReadFileOrThrow(file);
      htmlext::PrintHtmlDot(hext::Html(html), std::cout);
      return EXIT_SUCCESS;
    }

    std::vector<hext::Hext> extractors;
    std::vector<hext::Html> inputs;

    try
    {
      auto hext_filenames = po.get_hext_input();
      extractors.reserve(hext_filenames.size());
      for(const auto& filename : hext_filenames)
      {
        try
        {
          extractors.emplace_back(htmlext::ReadFileOrThrow(filename));
        }
        catch( const hext::SyntaxError& e )
        {
          std::cerr << argv[0] << ": Error in " << filename << ": "
                    << e.what() << "\n";
          return EXIT_FAILURE;
        }
      }

      if( po.contains("lint") )
        return EXIT_SUCCESS;

      auto html_filenames = po.get_html_input();
      inputs.reserve(html_filenames.size());
      for(const auto& filename : html_filenames)
        inputs.emplace_back(htmlext::ReadFileOrThrow(filename));
    }
    catch( const htmlext::FileError& e )
    {
      std::cerr << argv[0] << ": Error: " << e.what() << "\n";
      return EXIT_FAILURE;
    }

    for(const auto& hext : extractors)
    {
      for(const auto& html : inputs)
      {
        std::unique_ptr<hext::ResultTree> result = hext.extract(html);
        if( po.contains("print-result-dot") )
        {
          htmlext::PrintResultTreeDot(result.get(), std::cout);
        }
        else
        {
          auto json_opt = po.get_json_options();
          htmlext::PrintJson(result.get(), json_opt, std::cout);
        }
      }
    }
  }
  catch( const boost::program_options::error& e )
  {
    std::cerr << argv[0] << ": Argument error: " << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

