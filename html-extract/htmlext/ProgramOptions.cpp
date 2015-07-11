#include "htmlext/ProgramOptions.h"


namespace htmlext {


ProgramOptions::ProgramOptions()
: desc_("Options"),
  vm_()
{
  namespace po = boost::program_options;
  this->desc_.add_options()
    ("hext,x", po::value<std::vector<std::string>>(), "Hext file(s)")
    ("html,i", po::value<std::vector<std::string>>(), "HTML input file(s)")
    ("compact,c", "Print one JSON object per line")
    ("pretty,p", "Force pretty-printing JSON. Overrrides --compact")
    ("array,a", "Put results into one top-level JSON array. If combined"
                " with --compact, only print a single line")
    ("print-html-dot,d", po::value<std::string>(),
                         "Print HTML input file as DOT")
    ("print-result-dot,r", "Print ResultTree as DOT")
    ("lint,l", "Hext syntax check: parse hext and exit")
    ("help,h", "Print this help message and exit")
    ("version,V", "Print version information and exit")
  ;
}

void ProgramOptions::store_and_validate_or_throw(int argc, const char * argv[])
{
  namespace po = boost::program_options;

  po::positional_options_description pos_opt;
  pos_opt.add("hext", 1);
  pos_opt.add("html", -1);

  po::store(
    po::command_line_parser(argc, argv)
      .options(this->desc_)
      .positional(pos_opt)
      .run(),
    this->vm_
  );
  po::notify(this->vm_);

  if( this->contains("help") || this->contains("version") )
    return;

  if( this->contains("print-html-dot") )
    return;

  if( !this->contains("hext") )
    throw po::error("missing option --hext");

  if( this->contains("lint") )
    return;

  if( !this->contains("html") )
    throw po::error("missing option --html-input");
}

bool ProgramOptions::contains(const char * key) const
{
  return this->vm_.count(key);
}

std::string ProgramOptions::get(const char * key) const
{
  return this->vm_[key].as<std::string>();
}

std::vector<std::string> ProgramOptions::get_hext_input() const
{
  return this->vm_["hext"].as<std::vector<std::string>>();
}

std::vector<std::string> ProgramOptions::get_html_input() const
{
  return this->vm_["html"].as<std::vector<std::string>>();
}

void ProgramOptions::print(const char * program_name, std::ostream& out) const
{
  out << "Usage:\n  "
      << program_name
      << " [options] <hext-file> <html-file...>\n"
         "      Apply extraction rules from hext-file to each html-file.\n"
         "      Print result as JSON.\n\n  "
      << program_name
      << " -l <hext-file>\n"
         "      Parse hext-file and exit silently on success.\n"
         "      On failure, print error information to stderr.\n\n  "
      << program_name
      << " --print-html-dot <html-file>\n"
         "      Parse and print html-file as DOT.\n\n"
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

