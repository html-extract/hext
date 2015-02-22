#ifndef HEXT_ATTRIBUTE_CAPTURE_H
#define HEXT_ATTRIBUTE_CAPTURE_H

#include <string>
#include <iostream>

#include <gumbo.h>

#include "hext/pattern/capture-pattern.h"


namespace hext {


/// An AttributeCapture is a CapturePattern that is used to capture whole
/// attribute values from html-nodes.
class AttributeCapture : public CapturePattern
{
public:
  AttributeCapture(
    const std::string& result_name,
    const std::string& attr_name,
    const std::string& regex
  );
  MatchTree::NameValuePair capture(const GumboNode * node) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  const GumboAttribute * get_node_attr(const GumboNode * node) const;

  /// The name of the html-node-attribute whose value should be captured
  const std::string attr;
};


} // namespace hext


#endif // HEXT_ATTRIBUTE_CAPTURE_H

