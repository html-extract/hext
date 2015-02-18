#include "hext/file.h"


namespace hext {


file_error::file_error(const std::string& msg)
: std::runtime_error(msg)
{
}


std::string read_file_or_throw(const std::string& path)
{
  std::ifstream file(path, std::ios::in | std::ios::binary);

  if( file.fail() )
    throw file_error(
      "cannot access '" + path + "': " + std::strerror(errno)
    );

  std::string buffer;
  file.seekg(0, std::ios::end);

  if( file.fail() || file.tellg() < 0 )
    throw file_error(
      "cannot read '" + path + "': " + std::strerror(errno) +
      " (not a regular file?)"
    );

  buffer.resize(file.tellg());
  file.seekg(0, std::ios::beg);
  file.read(&buffer[0], buffer.size());

  if( file.fail() )
    throw file_error(
      "cannot read '" + path + "': " + std::strerror(errno)
    );

  return buffer;
}


} // namespace hext
