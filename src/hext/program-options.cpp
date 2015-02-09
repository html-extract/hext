#include "hext/program-options.h"


namespace hext {


program_options::program_options(int argc, const char * argv[])
: desc("Options"),
  vm()
{
  namespace po = boost::program_options;

  this->desc.add_options()
    ("help,h", "This help message")
    ("hext-file,f", po::value<std::string>(), "Path to hext file")
    ("html-file,i", po::value<std::string>(), "Path to html file")
    ("lint,l", "Hext syntax check")
    ("print,p", "Print parsed hext")
    ("print-debug,d", "Print hext with match_count")
    ("keep-invalid,k", "Do not remove invalid matches")
    ("mt-graph,g", "Print match-tree as DOT")
  ;

  po::store(po::parse_command_line(argc, argv, this->desc), this->vm);
  po::notify(this->vm);
}

bool program_options::contains(const char * key) const
{
  return this->vm.count(key);
}

std::string program_options::get(const char * key) const
{
  return this->vm[key].as<std::string>();
}

void program_options::print(const char * program_name, std::ostream& out) const
{
  out << "Usage:\n"
      << program_name << " -h hext-file -i html-file\n";
  out << this->desc;
}

bool program_options::validate_or_print_error(std::ostream& out) const
{
  if( !this->contains("hext-file") )
  {
    out << "Error: Expecting hext-file\n";
    return false;
  }

  if( this->contains("print") || this->contains("lint") )
    return true;

  if( !this->contains("html-file") )
  {
    out << "Error: Expecting html-file\n";
    return false;
  }

  return true;
}


} // namespace hext

