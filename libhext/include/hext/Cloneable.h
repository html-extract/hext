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

#ifndef HEXT_CLONEABLE_H_INCLUDED
#define HEXT_CLONEABLE_H_INCLUDED

/// @file
///   Defines template hext::Cloneable

#include "hext/Visibility.h"

#include <memory>
#include <type_traits>


namespace hext {


/// Curiously recurring template pattern that extends a base class to provide
/// a virtual method Cloneable::clone().
///
/// @tparam Derived:  A subclass of Cloneable that is copy constructible.
/// @tparam    Base:  The base class that shall be extended.
template<typename Derived, typename Base>
class HEXT_PUBLIC Cloneable : public Base
{
public:
  /// Clones objects of template type Derived and returns an owning pointer to
  /// the newly allocated Base.
  ///
  /// Fails at compile time if template parameter Base is not a base of template
  /// parameter Derived or if template parameter Derived is not copy
  /// constructible.
  virtual std::unique_ptr<Base> clone() const
  {
    static_assert(std::is_base_of<Base, Derived>::value,
        "template argument <Base> is not a base of "
        "template argument <Derived>");
    static_assert(std::is_copy_constructible<Derived>::value,
        "template argument <Derived> is not copy constructible");
    // This static_cast is safe because we have just asserted that Derived is a
    // subclass of Base.
    return std::make_unique<Derived>(static_cast<const Derived&>(*this));
  }
};


} // namespace hext


#endif // HEXT_CLONEABLE_H_INCLUDED

