#ifndef HEXT_PROGRAM_OPTIONS_H
#define HEXT_PROGRAM_OPTIONS_H

#include <string>
#include <iostream>

#include <boost/program_options.hpp>


namespace hext {


// The project's program options.
class ProgramOptions
{
public:
  ProgramOptions();
  ~ProgramOptions();

  /// Store argv and validate or throw boost::program_options::error.
  void store_and_validate_or_throw(int argc, const char * argv[]);
  /// Check if key was given as an argument.
  bool contains(const char * key) const;
  /// Get value from parameter.
  std::string get(const char * key) const;
  /// Print usage and options.
  void print(const char * program_name, std::ostream& out = std::cout) const;

private:
  boost::program_options::options_description desc_;
  boost::program_options::variables_map vm_;
};


} // namespace hext


#endif // HEXT_PROGRAM_OPTIONS_H

