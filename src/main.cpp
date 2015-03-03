#include "hext/parser.h"
#include "hext/html.h"
#include "hext/file.h"
#include "hext/program-options.h"

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ios>
#include <vector>

#include <boost/regex/pattern_except.hpp>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


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

    const std::string bf_hext = hext::ReadFileOrThrow(po.get("hext-file"));
    hext::Parser p(
      bf_hext.c_str(),
      bf_hext.c_str() + bf_hext.size()
    );
    auto rules = p.parse();

    if( po.contains("print") )
    {
      for(const auto& r : rules)
        r.print();
      return EXIT_SUCCESS;
    }

    if( po.contains("lint") )
      return EXIT_SUCCESS;

    const std::string bf_html = hext::ReadFileOrThrow(po.get("html-file"));
    const hext::Html html(bf_html.c_str(), bf_html.size());

    for(const auto& rule : rules)
    {
      std::unique_ptr<hext::MatchTree> mt = html.extract(rule);
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
        std::vector<rapidjson::Document> objects = mt->to_json();
        for(const auto& obj : objects)
        {
          rapidjson::StringBuffer buffer;
          rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
          obj.Accept(writer);
          std::cout << buffer.GetString() << "\n";
        }
      }
    }
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

