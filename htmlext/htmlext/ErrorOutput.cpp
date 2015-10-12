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

#include "htmlext/ErrorOutput.h"


namespace htmlext {


ErrorOutput::ErrorOutput(const char * error_source, std::ostream& out) noexcept
: out_(out)                      // noexcept
, source_(error_source)          // noexcept
, isatty_(isatty(STDERR_FILENO)) // noexcept
{
}

void ErrorOutput::print(const std::string& title,
                        const std::string& contents) const
{
  this->out_ << ( this->isatty_ ? ErrorOutput::esc_red_ : "" )
             << this->source_ << ": "
             << title << ": "
             << ( this->isatty_ ? ErrorOutput::esc_reset_ : "" )
             << contents << "\n";
}


} // namespace htmlext

