#ifndef HEXT_ATTRIBUTE_CAPTURE_H
#define HEXT_ATTRIBUTE_CAPTURE_H

#include <string>
#include <iostream>

#include <gumbo.h>

#include "hext/capture-pattern.h"


namespace hext {


/// An attribute_capture is a capture_pattern that is used to capture whole
/// attribute values from html-nodes.
class attribute_capture : public capture_pattern
{
public:
  attribute_capture(
    const std::string& result_name,
    const std::string& attr_name,
    const std::string& regex
  );
  match_tree::name_value_pair capture(const GumboNode * node) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  const GumboAttribute * get_node_attr(const GumboNode * node) const;

  /// The name of the html-node-attribute whose value should be captured
  const std::string attr;
};


} // namespace hext


#endif // HEXT_ATTRIBUTE_CAPTURE_H

