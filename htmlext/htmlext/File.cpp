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

