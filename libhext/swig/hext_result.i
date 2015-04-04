%include "std_multimap.i"
%include "std_vector.i"
%include "std_string.i"

namespace std
{
  %template(ResultMap) multimap<std::string, std::string>;
  %template(Result) vector<std::multimap<std::string, std::string>>;
}

