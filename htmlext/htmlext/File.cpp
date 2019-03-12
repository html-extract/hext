// Copyright 2015 Thomas Trapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "htmlext/File.h"

#include <fstream>
#include <sstream>
// strerror_r, strerror_s are not part of the C++ stdlib
#include <string.h>


namespace {


/// Wrapper for strerror_r (GNU) and strerror_s (MSVC).
std::string StrError(int errnum)
{
  // Buffer size: There may be locales where error messages get huge in terms
  // of bytes and performance is no issue in my use case.
  std::string buffer(1024, '\0');
#ifdef _WIN32
  // strerror_s returns int 0 if it successfully populated the buffer.
  if( strerror_s(&buffer[0], buffer.size(), errnum) )
    return "error message unavailable";
  else
    return buffer;
#elif defined(_GNU_SOURCE)
  // strerror_r may use the buffer, but doesn't need to. It may return a
  // pointer to a string that is already available.
  return std::string(strerror_r(errnum, &buffer[0], buffer.size()));
#elif __APPLE__
  // strerror_r returns int 0 if it successfully populated the buffer.
  if( strerror_r(errnum, &buffer[0], buffer.size()) )
    return "error message unavailable";
  else
    return buffer;
#else
  #error "Unsupported platform. Please raise an issue on github."
#endif
}


} // namespace


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
        "cannot access '" + path + "': " + StrError(errno)
      );
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  if( file.fail() )
    throw FileError(
      "cannot read '" + path + "': " + StrError(errno)
    );

  return buffer.str();
}


} // namespace htmlext

