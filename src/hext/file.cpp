#include "hext/file.h"


namespace hext {


FileError::FileError(const std::string& msg)
: std::runtime_error(msg)
{
}


std::string read_file_or_throw(const std::string& path)
{
  std::ifstream file(path, std::ios::in | std::ios::binary);

  if( file.fail() )
    throw FileError(
      "cannot access '" + path + "': " + std::strerror(errno)
    );

  std::stringstream buffer;
  buffer << file.rdbuf();

  if( file.fail() )
    throw FileError(
      "cannot read '" + path + "': " + std::strerror(errno)
    );

  return buffer.str();
}


} // namespace hext

