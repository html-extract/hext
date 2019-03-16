// Copyright 2016 Thomas Trapp
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

%module hext

%include "typemaps.i"
%include "std_string.i"

// Convert vector of multimaps to an array of arrays
%typemap(out) std::vector<std::multimap<std::string, std::string>> {
  // Assuming $1 is of type SwigValueWrapper.
  array_init($result);
  for(const auto& map : *(&$1))
  {
    zval out_map;
    array_init(&out_map);

    auto it = map.cbegin();
    while( it != map.cend() )
    {
      if( map.count(it->first) < 2 )
      {
        add_assoc_string(
          &out_map,
          it->first.c_str(),
          it->second.c_str()
        );
        ++it;
      }
      else
      {
        // Pack values of non-unique keys into an indexed array
        zval values;
        array_init(&values);

        auto lower = map.lower_bound(it->first);
        auto upper = map.upper_bound(it->first);
        for(; lower != upper; ++lower)
          add_next_index_stringl(
            &values,
            lower->second.c_str(),
            lower->second.size()
          );

        add_assoc_zval(&out_map, it->first.c_str(), &values);
        it = upper;
      }
    }

    add_next_index_zval($result, &out_map);
  }
}

%include "exception.i"
%exception Rule::Rule {
  try
  {
    $action
  }
  catch(const hext::SyntaxError& e)
  {
    SWIG_exception(SWIG_ValueError, e.what());
  }
}

%ignore Html::root() const;
%{
#include "wrapper/Html.h"
#include "wrapper/Rule.h"
%}

// Swig has no builtin support for PHP namespaces; using unique prefix instead
%rename (HextRule) Rule;
%rename (HextHtml) Html;

%include "wrapper/Html.h"
%include "wrapper/Rule.h"

