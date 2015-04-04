%{
  #include "hext/Hext.h"
  using namespace hext;
%}

#include "hext/Option.h"

class Hext
{
public:
  explicit Hext(const std::string& hext, Option flags = DefaultOption);
  std::vector<std::multimap<std::string, std::string>>
  extract(const std::string& html) const;
};

