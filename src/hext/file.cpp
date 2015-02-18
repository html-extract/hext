#include "hext/file.h"


namespace hext {


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


} // namespace hext

