#ifndef HEXT_PROGRAM_OPTIONS_H
#define HEXT_PROGRAM_OPTIONS_H

#include <string>
#include <iostream>

#include <boost/program_options.hpp>


namespace hext {


class program_options
{
public:
  program_options(int argc, const char * argv[]);

  bool contains(const char * key) const;

  std::string get(const char * key) const;

  void print(const char * program_name, std::ostream& out = std::cout) const;

  bool validate_or_print_error(std::ostream& out = std::cerr) const;

private:
  boost::program_options::options_description desc;
  boost::program_options::variables_map vm;
};


} // namespace hext


#endif // HEXT_PROGRAM_OPTIONS_H

