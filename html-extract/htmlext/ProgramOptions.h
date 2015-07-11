#ifndef HTMLEXT_PROGRAM_OPTIONS_H_INCLUDED
#define HTMLEXT_PROGRAM_OPTIONS_H_INCLUDED

#include "htmlext/Json.h"

#include <string>
#include <vector>
#include <iostream>

#include <unistd.h>

#include <boost/program_options.hpp>


namespace htmlext {


// The htmlext's program options.
class ProgramOptions
{
public:
  ProgramOptions();

  /// Store argv and validate or throw boost::program_options::error.
  void store_and_validate_or_throw(int argc, const char * argv[]);

  /// Check if key was given as an argument.
  bool contains(const char * key) const;

  /// Get value from parameter.
  std::string get(const char * key) const;

  /// Return all hext-input filenames.
  std::vector<std::string> get_hext_input() const;

  /// Return all html-input filenames.
  std::vector<std::string> get_html_input() const;

  /// Print usage and options.
  void print(const char * program_name, std::ostream& out = std::cout) const;

  /// Return JSON options as given on the command line.
  JsonOption get_json_options() const;

private:
  boost::program_options::options_description desc_;
  boost::program_options::variables_map vm_;
};


} // namespace htmlext


#endif // HTMLEXT_PROGRAM_OPTIONS_H_INCLUDED

