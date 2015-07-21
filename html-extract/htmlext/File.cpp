#include "htmlext/File.h"


namespace htmlext {


FileError::FileError(const std::string& msg) noexcept
: std::runtime_error(msg)  // noexcept
{
}


std::string ReadFileOrThrow(const std::string& path)
{
  std::ifstream file(path, std::ios::in | std::ios::binary);

  if( file.fail() )
  {
    if( path == "-" )
      return ReadFileOrThrow("/dev/stdin");
    else
      throw FileError(
        "cannot access '" + path + "': " + std::strerror(errno)
      );
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  if( file.fail() )
    throw FileError(
      "cannot read '" + path + "': " + std::strerror(errno)
    );

  return buffer.str();
}


} // namespace htmlext

