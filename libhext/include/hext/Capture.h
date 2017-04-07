// Copyright 2015-2017 Thomas Trapp
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

#ifndef HEXT_CAPTURE_H_INCLUDED
#define HEXT_CAPTURE_H_INCLUDED

/// @file
///   Declares hext::Capture

#include "hext/Result.h"
#include "hext/Visibility.h"

#include <memory>
#include <optional>

#include <gumbo.h>


namespace hext {


/// Abstract base for every Capture.
///
/// Captures are applied to HTML elements with Capture::capture() which will
/// return either a ResultPair, or an empty optional if there was nothing to
/// capture.
///
/// Note: You probably don't want to inherit from this class directly, unless
///       you want to provide your own Capture::clone() method. If your subclass
///       has a copy constructor, you can extend from
///       hext::Cloneable<YourSubclass, hext::Capture> which provides a generic
///       clone method.
class HEXT_PUBLIC Capture
{
public:
  Capture() noexcept = default;
  Capture(const Capture&) = default;
  Capture(Capture&&) noexcept = default;
  Capture& operator=(const Capture&) = default;
  Capture& operator=(Capture&&) noexcept = default;
  virtual ~Capture() noexcept = default;

  /// Clones derived object.
  virtual std::unique_ptr<Capture> clone() const = 0;

  /// Returns a name/value pair with the captured contents or an empty optional,
  /// if there was nothing to capture.
  virtual std::optional<ResultPair> capture(const GumboNode * node) const = 0;
};


} // namespace hext


#endif // HEXT_CAPTURE_H_INCLUDED

