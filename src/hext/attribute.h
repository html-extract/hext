#ifndef HEXT_ATTRIBUTE_H
#define HEXT_ATTRIBUTE_H

#include <string>

#include <gumbo.h>

#include "hext/match-tree.h"
#include "hext/builtin-captures.h"


namespace hext {


class attribute
{
public:
  attribute();

  bool is_capture() const;
  void set_is_capture(bool capt);

  void set_name(const std::string& attribute_name);
  void set_value(const std::string& attribute_value);

  bool matches(const GumboNode * node) const;

  match_tree::name_value_pair capture(const GumboNode * node) const;

  void print(std::ostream& out = std::cout) const;

private:
  std::string name;
  std::string value;
  bool is_capt;
  bool is_built;
};


} // namespace hext


#endif // HEXT_ATTRIBUTE_H

