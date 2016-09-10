// Copyright 2015, 2016 Thomas Trapp
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

#ifndef HEXT_COLLAPSEWSPIPE_H_INCLUDED
#define HEXT_COLLAPSEWSPIPE_H_INCLUDED

/// @file
///   Declares hext::CollapseWsPipe

#include "hext/Cloneable.h"
#include "hext/StringPipe.h"
#include "hext/Visibility.h"

#include <string>


namespace hext {


/// Removes whitespace from beginning and end and collapses multiple whitespace
/// to a single space.
///
/// @par Example:
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// "   Like\na Rolling\n\tStone  "
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// becomes
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// "Like a Rolling Stone"
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class HEXT_PUBLIC CollapseWsPipe final
  : public hext::Cloneable<CollapseWsPipe, StringPipe>
{
public:
  /// Collapses multiple whitespace to a single space
  std::string transform(std::string str) const override;
};


} // namespace hext


#endif // HEXT_COLLAPSEWSPIPE_H_INCLUDED

