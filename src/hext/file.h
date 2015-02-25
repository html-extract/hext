#ifndef HEXT_FILE_H
#define HEXT_FILE_H

#include <cassert>
#include <string>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <sstream>


namespace hext {


class FileError : public std::runtime_error
{
public:
  explicit FileError(const std::string& msg);
};


// Read file at path to buffer. Throws FileError on failure.
std::string ReadFileOrThrow(const std::string& path);


} // namespace hext


#endif // HEXT_FILE_H

