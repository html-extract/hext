// Copyright 2016-2021 Thomas Trapp
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

%begin %{
// Python 2: Allow conversion of unicode strings to std::string and char *.
//   By SWIG's default, only byte strings are converted to std::string or
//   char *. This does not affect Python 3.
//   http://swig.org/Doc3.0/Python.html#Python_2_unicode
#define SWIG_PYTHON_2_UNICODE
%}

%include "typemaps.i"
%include "stdint.i"
%include "std_multimap.i"
%include "std_vector.i"
%include "std_string.i"


%inline %{


namespace {


struct ScopedPyObject
{
  explicit ScopedPyObject(PyObject * object) noexcept
  : obj(object)
  {}

  ~ScopedPyObject() noexcept { Py_DECREF(this->obj); }

  PyObject * obj;
};


} // namespace


%} // %inline


// Convert vector of multimaps to list of dicts
%typemap(out) std::vector<std::multimap<std::string, std::string>>
{
  $result = PyList_New(0);
  if( !$result )
    SWIG_exception(SWIG_RuntimeError, "PyList_New returned nullptr");

  for(const auto& map : *(&$1))
  {
    ScopedPyObject dict(PyDict_New());
    if( !dict.obj )
      SWIG_exception(SWIG_RuntimeError, "PyDict_New returned nullptr");

    auto it = map.cbegin();
    while( it != map.cend() )
    {
      if( map.count(it->first) < 2 )
      {
        ScopedPyObject value(PyString_FromString(it->second.c_str()));
        if( !value.obj )
          SWIG_exception(SWIG_RuntimeError,
              "PyString_FromString returned nullptr");

        // does not steal a reference to value
        if( PyDict_SetItemString(dict.obj, it->first.c_str(), value.obj) )
          SWIG_exception(SWIG_RuntimeError,
              "PyDict_SetItemString returned != 0");

        ++it;
      }
      else
      {
        ScopedPyObject list(PyList_New(0));
        if( !list.obj )
          SWIG_exception(SWIG_RuntimeError, "PyList_New returned nullptr");

        auto lower = map.lower_bound(it->first);
        auto upper = map.upper_bound(it->first);
        for(; lower != upper; ++lower)
        {
          // Swig defines PyString_FromString, which forwards to
          // PyUnicode_FromString
          ScopedPyObject value(PyString_FromString(lower->second.c_str()));
          if( !value.obj )
            SWIG_exception(SWIG_RuntimeError,
                "PyString_FromString returned nullptr");

          // does not steal a reference to value
          if( PyList_Append(list.obj, value.obj) )
            SWIG_exception(SWIG_RuntimeError, "PyList_Append returned != 0");
        }

        // does not steal a reference to list
        if( PyDict_SetItemString(dict.obj, it->first.c_str(), list.obj) )
          SWIG_exception(SWIG_RuntimeError,
              "PyDict_SetItemString returned != 0");

        it = upper;
      }
    }

    // does not steal a reference to dict
    if( PyList_Append($result, dict.obj) )
      SWIG_exception(SWIG_RuntimeError, "PyList_Append returned != 0");
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
%exception Rule::extract {
  try
  {
    $action
  }
  catch(const hext::MaxSearchError& e)
  {
    SWIG_exception(SWIG_RuntimeError, e.what());
  }
}

%ignore Html::root() const;
%{
#include "wrapper/Html.h"
#include "wrapper/Rule.h"
%}
%include "wrapper/Html.h"
%include "wrapper/Rule.h"

