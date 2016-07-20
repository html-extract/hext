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

#ifndef HTMLEXT_PROGRAM_OPTIONS_H_INCLUDED
#define HTMLEXT_PROGRAM_OPTIONS_H_INCLUDED

#include "htmlext/Json.h"

#include <string>
#include <vector>
#include <iostream>

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
  std::vector<std::string> get_hext_files() const;

  /// Return all hext-input supplied directly on cmdline.
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

