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
  %template(StdResultMap) multimap<std::string, std::string>;
  %template(StdResult) vector<std::multimap<std::string, std::string>>;
}

class Hext
{
public:
  explicit Hext(const std::string& hext, Option flags = DefaultOption);

  std::vector<std::multimap<std::string, std::string>>
  extract(const std::string& html) const;
};

