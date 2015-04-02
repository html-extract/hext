%{
#include "hext/Hext.h"
using namespace hext;
%}

%include "stl.i"
%include "std_string.i"
%include "std_multimap.i"
%include "std_vector.i"
%include "exception.i"
%include "hext/Option.h"

namespace std
{
  %template(StdResultMap) multimap<std::string, std::string>;
  %template(StdResult) vector<std::multimap<std::string, std::string>>;
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

class Hext
{
public:
  explicit Hext(const std::string& hext, Option flags = DefaultOption);

  std::vector<std::multimap<std::string, std::string>>
  extract(const std::string& html) const;
};


