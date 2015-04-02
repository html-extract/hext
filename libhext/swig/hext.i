%{
#include "hext/Hext.h"
using namespace hext;
%}

%include "stl.i"
%include "std_string.i"
%include "std_map.i"
%include "std_vector.i"
%include "exception.i"
%include "hext/Option.h"

namespace std
{
  %template(StdResultMap) map<std::string, std::string>;
  %template(StdResult) vector<std::map<std::string, std::string>>;
}

%exception {
  try
  {
    $action
  }
  catch(const ParseError& e)
  {
    SWIG_exception(SWIG_ValueError, e.what());
  }
}

// Hext::extract returns a multimap, a data structure that isn't available
// natively in some (most?) scripting languages. Although swig does provide
// std_multimap.i for python, it is missing for some other languages (e.g.
// PHP). The easiest way is to convert the multimap to a map, since std_map.i
// is available for every target language that swig supports.

// Create a new method "extract" that wraps the original Hext::extract and
// returns a std::map instead of a std::multimap.
%extend Hext {
  std::vector<std::map<std::string, std::string>>
  extract(const std::string& html) const
  {
    typedef
      std::vector<std::multimap<std::string, std::string>>
      result_type;
    typedef
      std::vector<std::map<std::string, std::string>>
      output_type;

    result_type result = $self->extract(html);
    output_type output(result.size());
    for(result_type::size_type i = 0; i < result.size(); ++i)
    {
      std::map<std::string, std::string> result_map;
      for(const auto& p : result[i])
      {
        // Overwrite already existing keys (same behaviour as python's
        // std_multimap.i).
        result_map[p.first] = p.second;
      }
      output[i] = result_map;
    }

    return output;
  }
}

class Hext
{
public:
  explicit Hext(const std::string& hext, Option flags = DefaultOption);
};

