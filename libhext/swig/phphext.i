%module phphext

%{
  #include "hext/Hext.h"
  using namespace hext;
%}

%include "hext_exception.i"
%include "std_string.i"

// Convert vector of multimaps to array of arrays, because swig has no
// std_multimap.i for PHP.
%typemap(out) std::vector<std::multimap<std::string, std::string>> {
  // Assuming $1 is of type SwigValueWrapper.
  array_init($result);
  for(const auto& map : *(&$1))
  {
    zval * out_map;
    MAKE_STD_ZVAL(out_map);
    array_init(out_map);

    for(const auto& p : map)
    {
      // Overwrite already existing keys (same behaviour as python's
      // std_multimap.i).
      add_assoc_string(
        out_map,
        p.first.c_str(),
        // Since we request that the string should be copied, this const_cast
        // should be safe.
        const_cast<char *>(p.second.c_str()),
        // Copy the string
        1
      );
    }

    add_next_index_zval($result, out_map);
  }
}

#include "hext/Option.h"

class Hext
{
public:
  explicit Hext(const std::string& hext, Option flags = DefaultOption);
  std::vector<std::multimap<std::string, std::string>>
  extract(const std::string& html) const;
};

