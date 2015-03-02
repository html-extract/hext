#ifndef HEXT_FILE_H_INCLUDED
#define HEXT_FILE_H_INCLUDED

#include <cassert>
#include <string>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <sstream>


namespace hext {


/// Custom exception type for file errors.
class FileError : public std::runtime_error
{
public:
  explicit FileError(const std::string& msg);
};


/// Read file at path to buffer. Throws FileError on failure.
/// Can read regular files as well as named pipes.
std::string ReadFileOrThrow(const std::string& path);


} // namespace hext


#endif // HEXT_FILE_H_INCLUDED

