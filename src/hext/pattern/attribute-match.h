#ifndef HEXT_ATTRIBUTE_MATCH_H
#define HEXT_ATTRIBUTE_MATCH_H

#include <string>
#include <iostream>
#include <memory>

#include <gumbo.h>

#include "hext/pattern/attr-test.h"
#include "hext/pattern/match-pattern.h"


namespace hext {


/// An attribute_match is a match_pattern that checks whether an html-node has
/// any attribute called attr_name.
class attribute_match : public match_pattern
{
public:
  attribute_match(
    const std::string& attr_name,
    std::unique_ptr<attr_test> attribute_test
  );
  match_result matches(const GumboNode * node) const final;
  void print(std::ostream& out = std::cout) const final;

protected:
  /// Get a GumboAttribute pointer to the node's attribute called attr_name.
  /// Returns nullptr if not found.
  const GumboAttribute * get_node_attr(const GumboNode * node) const;
  const std::string attr;
};


} // namespace hext


#endif // HEXT_ATTRIBUTE_MATCH_H

