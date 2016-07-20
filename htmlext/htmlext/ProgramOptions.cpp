// Copyright 2015 Thomas Trapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "htmlext/ProgramOptions.h"

#ifdef _WIN32
#include <io.h>
#define isatty _isatty
#define STDOUT_FILENO 1
#else
#include <unistd.h>
#endif


namespace htmlext {


ProgramOptions::ProgramOptions()
: desc_("Options"),
  vm_()
{
  namespace po = boost::program_options;
  this->desc_.add_options()
    ("hext,x", po::value<std::vector<std::string>>()
                   ->default_value(std::vector<std::string>(), "")
                   ->value_name("<file>"),
               "Add Hext from file")
    ("html,i", po::value<std::vector<std::string>>()
                   ->value_name("<file>"),
               "Add HTML from file")
    ("str,s", po::value<std::vector<std::string>>()
                  ->default_value(std::vector<std::string>(), "")
                  ->value_name("<string>"),
              "Add Hext from string")
    ("compact,c", "Print one JSON object per line")
    ("pretty,p", "Pretty-print JSON")
    ("array,a", "Wrap results in a JSON array")
    ("filter,f", po::value<std::string>()
                     ->value_name("<key>"),
                 "Print values whose name matches <key>")
    ("lint,l", "Do Hext syntax check")
    ("help,h", "Print this help message")
    ("version,V", "Print info and version")
  ;
}

void ProgramOptions::store_and_validate_or_throw(int argc, const char * argv[])
{
  namespace po = boost::program_options;

  po::command_line_parser cli_parser(argc, argv);
  po::positional_options_description pos_opt;
  cli_parser.options(this->desc_);

  // If --lint was given, then do not add positional options to avoid
  // confusion. For example, the following would only parse first.hext,
  // but not second.hext because it is interpreted as the positional
  // option <html-file>:
  // ./htmlext --lint first.hext second.hext
  const auto end = argv + argc;
  if( std::find(argv, end, std::string("-l")) == end &&
      std::find(argv, end, std::string("--lint")) == end )
  {
    pos_opt.add("hext", 1);
    pos_opt.add("html", -1);
    cli_parser.positional(pos_opt);
  }

  po::store(cli_parser.run(), this->vm_);
  po::notify(this->vm_);

  if( this->contains("help") || this->contains("version") )
    return;

  if( !this->contains("hext") && !this->contains("str") )
    throw po::error("missing Hext input, use --hext/-x <file> "
                    "or --str/-s <string>");

  if( this->contains("lint") )
    return;

  if( !this->contains("html") )
    throw po::error("missing HTML input, use --html/-i <html-file>");
}

bool ProgramOptions::contains(const char * key) const
{
  return this->vm_.count(key) && !this->vm_[key].defaulted();
}

std::string ProgramOptions::get(const char * key) const
{
  return this->vm_[key].as<std::string>();
}

std::vector<std::string> ProgramOptions::get_hext_files() const
{
  return this->vm_["hext"].as<std::vector<std::string>>();
}

std::vector<std::string> ProgramOptions::get_hext_input() const
{
  return this->vm_["str"].as<std::vector<std::string>>();
}

std::vector<std::string> ProgramOptions::get_html_input() const
{
  return this->vm_["html"].as<std::vector<std::string>>();
}

void ProgramOptions::print(const char * program_name, std::ostream& out) const
{
  out << program_name << " - Extract structured content from HTML.\n\n"
      << "Usage:\n  "
      << program_name
      << " [options] <hext-file> <html-file...>\n"
         "      Apply extraction rules from <hext-file> to each\n"
         "      <html-file> and print the captured content as JSON.\n\n"
      << this->desc_;
}

JsonOption ProgramOptions::get_json_options() const
{
  using htmlext::operator|;
  htmlext::JsonOption opt = htmlext::JsonOption::NoOption;

  // --pretty takes precedence over --compact
  if( this->contains("pretty") ||
      // by default, pretty print JSON if not piping to a file or pipe
      ( !this->contains("compact") && isatty(STDOUT_FILENO) ) )
    opt = opt | htmlext::JsonOption::PrettyPrint;

  if( this->contains("array") )
    opt = opt | htmlext::JsonOption::ArrayEnvelope;

  return opt;
}


} // namespace htmlext

