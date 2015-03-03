#ifndef HEXT_PATTERN_ATTRIBUTE_CAPTURE_H_INCLUDED
#define HEXT_PATTERN_ATTRIBUTE_CAPTURE_H_INCLUDED

#include "hext/pattern/capture-pattern.h"

#include <string>
#include <iostream>

#include <gumbo.h>
#include <boost/regex.hpp>


namespace hext {


/// An AttributeCapture is a CapturePattern that is used to capture whole
/// attribute values from html-nodes.
class AttributeCapture : public CapturePattern
{
public:
  AttributeCapture(
    const std::string& result_name,
    const std::string& attr_name
  );
  AttributeCapture(
    const std::string& result_name,
    const std::string& attr_name,
    const boost::regex& regex
  );
  MatchTree::NameValuePair capture(const GumboNode * node) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  /// The name of the html-node-attribute whose value should be captured
  const std::string attr_;
};


} // namespace hext


#endif // HEXT_PATTERN_ATTRIBUTE_CAPTURE_H_INCLUDED

