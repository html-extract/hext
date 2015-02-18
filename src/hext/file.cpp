#include "hext/file.h"


namespace hext {


file_error::file_error(const std::string& msg)
: std::runtime_error(msg)
{
}


std::string read_file(std::ifstream& file)
{
  assert(!file.fail());

  std::string buffer;

  file.seekg(0, std::ios::end);
  buffer.resize(file.tellg());
  file.seekg(0, std::ios::beg);
  file.read(&buffer[0], buffer.size());

  return buffer;
}

std::string read_file_or_throw(const std::string& path)
{
  std::ifstream file(path, std::ios::in | std::ios::binary);

  if( file.fail() )
    throw file_error(
      "cannot access '" + path + "': " + std::strerror(errno)
    );

  std::string buffer = read_file(file);

  if( file.fail() )
    throw file_error(
      "cannot read '" + path + "': " + std::strerror(errno)
    );

  return buffer;
}


} // namespace hext

