#ifndef HEXT_ATTRIBUTE_H
#define HEXT_ATTRIBUTE_H

#include <string>
#include <iostream>
#include <boost/regex.hpp>

#include <gumbo.h>

#include "hext/match-tree.h"
#include "hext/builtin-captures.h"


namespace hext {


/// An attribute is a key-value pair of a rule.
/// An attribute may be
/// * a builtin attribute (e.g. hext-inner-text="(:title)"),
/// * a capture attribute (e.g. class="(:class_name)"), or
/// * a literal attribute (e.g. id="container")
class attribute
{
public:
  attribute(
    const std::string& attr_name,
    const std::string& attr_value,
    bool capture_contents
  );

  bool is_capture() const;

  /// Check if a GumboNode can satisfy this attribute.
  /// Returns true on match.
  bool matches(const GumboNode * node) const;

  /// Extract a name_value_pair described by this attribute from a GumboNode.
  /// Returns empty value if there is no match.
  match_tree::name_value_pair capture(const GumboNode * node) const;

  void print(std::ostream& out = std::cout) const;

private:
  const std::string name;
  const std::string value;
  const bool is_capt;
  const bool is_built;
};


} // namespace hext


#endif // HEXT_ATTRIBUTE_H

