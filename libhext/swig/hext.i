%module hext
%{
#include "hext/Hext.h"
using namespace hext;
%}

%include "std_string.i"
%include "std_multimap.i"
%include "std_vector.i"
%include "hext/Option.h"

namespace std
{
  %template(stdResultMap) multimap<std::string, std::string>;
  %template(stdResult) vector<std::multimap<std::string, std::string>>;
}

class Hext
{
public:
  explicit Hext(const std::string& hext, Option flags = Option::Default);

  std::vector<std::multimap<std::string, std::string>>
  extract(const std::string& html) const;
};

