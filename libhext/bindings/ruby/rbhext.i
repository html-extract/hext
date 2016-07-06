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

// Convert vector of multimaps to Array of Hashes
%typemap(out) std::vector<std::multimap<std::string, std::string>>
{
  const auto& input = *(&$1);
  auto enc = rb_utf8_encoding();
  $result = rb_ary_new2(input.size());

  for(const auto& map : input)
  {
    auto hash = rb_hash_new();
    auto it = map.cbegin();
    while( it != map.cend() )
    {
      auto key = rb_enc_str_new(it->first.c_str(), it->first.size(), enc);
      if( map.count(it->first) < 2 )
      {
        auto value = rb_enc_str_new(it->second.c_str(), it->second.size(), enc);
        rb_hash_aset(hash, key, value);
        ++it;
      }
      else
      {
        auto ary = rb_ary_new();
        auto lower = map.lower_bound(it->first);
        auto upper = map.upper_bound(it->first);
        for(; lower != upper; ++lower)
          rb_ary_push(
              ary,
              rb_enc_str_new(
                lower->second.c_str(),
                lower->second.size(),
                enc));
        rb_hash_aset(hash, key, ary);
        it = upper;
      }
    }

    rb_ary_push($result, hash);
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
// Avoid name clash with hext::HtmlTag::RUBY
#ifdef RUBY
  #undef RUBY
#endif

#include "wrapper/Html.h"
#include "wrapper/Rule.h"
%}
%include "wrapper/Html.h"
%include "wrapper/Rule.h"

