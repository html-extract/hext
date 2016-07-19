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

#ifndef HTMLEXT_ERROR_OUTPUT_H_INCLUDED
#define HTMLEXT_ERROR_OUTPUT_H_INCLUDED

#include <iostream>
#include <string>
#ifndef _WIN32
#include <unistd.h>
#endif


namespace htmlext {


/// Helper class to output errors. Use ANSI escape codes to highlight source
/// and title of an error messsage if STDERR is a terminal.
class ErrorOutput
{
public:
  explicit ErrorOutput(const char * error_source,
                       std::ostream& out = std::cerr) noexcept;

  void print(const std::string& title, const std::string& contents) const;

private:
#ifndef _WIN32
  // Change foreground color to bold red
  static constexpr const char * esc_red_ = "\033[1;31m";
  static constexpr const char * esc_reset_ = "\033[0m";
#endif

  std::ostream& out_;
  const char * source_;
#ifndef _WIN32
  bool isatty_;
#endif
};


} // namespace htmlext


#endif // HTMLEXT_ERROR_OUTPUT_H_INCLUDED

