#ifndef HEXT_FILE_H
#define HEXT_FILE_H

#include <cassert>
#include <string>
#include <fstream>


namespace hext {


// Read complete file to buffer.
std::string read_file(std::ifstream& file);


} // namespace hext


#endif // HEXT_FILE_H

