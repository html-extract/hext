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

#ifndef HTMLEXT_FILE_H_INCLUDED
#define HTMLEXT_FILE_H_INCLUDED

#include <string>
#include <stdexcept>


namespace htmlext {


/// Custom exception type for file errors.
class FileError : public std::runtime_error
{
public:
  explicit FileError(const std::string& msg) noexcept;
};


/// Read file at path to buffer. Throws FileError on failure.
/// Can read regular files as well as named pipes.
std::string ReadFileOrThrow(const std::string& path);


} // namespace htmlext


#endif // HTMLEXT_FILE_H_INCLUDED

