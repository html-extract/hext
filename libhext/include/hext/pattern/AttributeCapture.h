#ifndef HEXT_PATTERN_ATTRIBUTE_CAPTURE_H_INCLUDED
#define HEXT_PATTERN_ATTRIBUTE_CAPTURE_H_INCLUDED

#include "hext/pattern/CapturePattern.h"

#include <string>

#include <gumbo.h>
#include <boost/regex.hpp>


namespace hext {


/// An AttributeCapture is a CapturePattern that extracts an html-attribute
/// from an html-node.
class AttributeCapture : public CapturePattern
{
public:
  /// Construct an AttributeCapture.
  ///
  /// \param result_name
  ///     The name of the capture.
  /// \param attr_name
  ///     The name of the attribute whose value should be captured.
  AttributeCapture(
    const std::string& result_name,
    const std::string& attr_name
  );

  /// Construct an AttributeCapture that has a regex. See class CapturePattern
  /// for an explanation on how the regex is applied to the attribute-value.
  ///
  /// \param result_name
  ///     The name of the capture.
  /// \param attr_name
  ///     The name of the attribute whose value should be captured.
  AttributeCapture(
    const std::string& result_name,
    const std::string& attr_name,
    const boost::regex& regex
  );

  /// Return a string pair containing the captured value. First member is
  /// `result_name_`, second member is the node-attribute of `node` called
  /// `attr_name_`. If the attribute isn't found, an empty string is used
  /// instead. If a regex was given, it will be applied to attribute-value,
  /// capturing only the desired result.
  ResultTree::NameValuePair capture(const GumboNode * node) const final;

private:
  /// The name of the html-node-attribute whose value should be captured
  const std::string attr_name_;
};


} // namespace hext


#endif // HEXT_PATTERN_ATTRIBUTE_CAPTURE_H_INCLUDED

