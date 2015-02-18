#ifndef HEXT_FILE_H
#define HEXT_FILE_H

#include <cassert>
#include <string>
#include <fstream>
#include <cstring>
#include <stdexcept>


namespace hext {


class file_error : public std::runtime_error
{
public:
  explicit file_error(const std::string& msg);
};


// Read complete file to buffer.
std::string read_file(std::ifstream& file);
// Read file at path to buffer. Throws file_error.
std::string read_file_or_throw(const std::string& path);


} // namespace hext


#endif // HEXT_FILE_H

