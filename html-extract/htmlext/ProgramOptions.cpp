#include "htmlext/ProgramOptions.h"


namespace htmlext {


ProgramOptions::ProgramOptions()
: desc_("Options"),
  vm_()
{
  namespace po = boost::program_options;
  this->desc_.add_options()
    ("hext,x", po::value<std::string>(), "Hext file")
    ("html-input,i", po::value<std::vector<std::string>>(), "Html input file(s)")
    ("keep-invalid,k", "Do not remove invalid results")
    ("no-auto-any-descendant,n", "Do not force top rules to be any descendant")
    ("lint,l", "Hext syntax check; parse hext and exit")
    ("help,h", "Print this help message and exit")
    ("version,V", "Print version information and exit")
  ;
}

void ProgramOptions::store_and_validate_or_throw(int argc, const char * argv[])
{
  namespace po = boost::program_options;

  po::positional_options_description pos_opt;
  pos_opt.add("hext", 1);
  pos_opt.add("html-input", -1);

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

  if( !this->contains("hext") )
    throw po::error("missing option --hext");

  if( this->contains("lint") )
    return;

  if( !this->contains("html-input") )
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

std::vector<std::string> ProgramOptions::get_html_input() const
{
  return this->vm_["html-input"].as<std::vector<std::string>>();
}

void ProgramOptions::print(const char * program_name, std::ostream& out) const
{
  out << "Usage:\n  "
      << program_name << " hext-file html-file [html-file(s)]\n\n"
      << this->desc_;
}


} // namespace htmlext

