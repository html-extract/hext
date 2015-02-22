#ifndef HEXT_PROGRAM_OPTIONS_H
#define HEXT_PROGRAM_OPTIONS_H

#include <string>
#include <iostream>

#include <boost/program_options.hpp>


namespace hext {


class ProgramOptions
{
public:
  ProgramOptions();
  ~ProgramOptions();

  void store(int argc, const char * argv[]);

  bool contains(const char * key) const;

  std::string get(const char * key) const;

  void print(const char * program_name, std::ostream& out = std::cout) const;

private:
  boost::program_options::options_description desc_;
  boost::program_options::variables_map vm_;
};


} // namespace hext


#endif // HEXT_PROGRAM_OPTIONS_H

