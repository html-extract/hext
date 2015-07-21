#ifndef HTMLEXT_ERROR_OUTPUT_H_INCLUDED
#define HTMLEXT_ERROR_OUTPUT_H_INCLUDED

#include <iostream>
#include <string>
#include <unistd.h>


namespace htmlext {


/// Helper class to output errors. Use ANSI escape codes to highlight source
/// and title of an error messsage if STDERR is a terminal.
class ErrorOutput
{
public:
  explicit ErrorOutput(
    const char * error_source,
    std::ostream& out = std::cerr
  ) noexcept;

  void print(const std::string& title, const std::string& contents) const;

private:
  // Change foreground color to bold red
  static constexpr const char * esc_red_ = "\033[1;31m";
  static constexpr const char * esc_reset_ = "\033[0m";

  std::ostream& out_;
  const char * source_;
  bool isatty_;
};


} // namespace htmlext


#endif // HTMLEXT_ERROR_OUTPUT_H_INCLUDED

