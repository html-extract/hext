#include "hext/program-options.h"


namespace hext {


ProgramOptions::ProgramOptions()
: desc_("Options"),
  vm_()
{
  namespace po = boost::program_options;
  this->desc_.add_options()
    ("help,h", "This help message")
    ("hext-file,f", po::value<std::string>(), "Path to hext file")
    ("html-file,i", po::value<std::string>(), "Path to html file")
    ("lint,l", "Hext syntax check")
    ("print,p", "Print parsed hext")
    ("print-debug,d", "Print hext with match_count")
    ("keep-invalid,k", "Do not remove invalid results")
    ("rt-graph,g", "Print result tree as DOT")
  ;
}

ProgramOptions::~ProgramOptions()
{
}

void ProgramOptions::store_and_validate_or_throw(int argc, const char * argv[])
{
  namespace po = boost::program_options;
  po::store(po::parse_command_line(argc, argv, this->desc_), this->vm_);
  po::notify(this->vm_);

  if( this->contains("help") )
    return;

  if( !this->contains("hext-file") )
    throw po::error("missing option --hext-file");

  if( this->contains("print") || this->contains("lint") )
    return;

  if( !this->contains("html-file") )
    throw po::error("missing option --html-file");
}

bool ProgramOptions::contains(const char * key) const
{
  return this->vm_.count(key);
}

std::string ProgramOptions::get(const char * key) const
{
  return this->vm_[key].as<std::string>();
}

void ProgramOptions::print(const char * program_name, std::ostream& out) const
{
  out << "Usage:\n"
      << program_name << " -h hext-file -i html-file\n";
  out << this->desc_;
}


} // namespace hext

