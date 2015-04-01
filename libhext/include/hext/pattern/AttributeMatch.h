#ifndef HEXT_PATTERN_ATTRIBUTE_MATCH_H_INCLUDED
#define HEXT_PATTERN_ATTRIBUTE_MATCH_H_INCLUDED

#include "hext/pattern/ValueTest.h"
#include "hext/pattern/ValueMatch.h"

#include <string>
#include <memory>

#include <gumbo.h>


namespace hext {


/// An AttributeMatch is a ValueMatch that matches if an html-node has
/// an attribute called `attr_name` whose value passes `value_test`.
class AttributeMatch : public ValueMatch
{
public:
  /// Construct an AttributeMatch.
  ///
  /// \param attr_name
  ///     The name of the html-node-attribute to test.
  /// \param value_test
  ///     The ValueTest which is to be applied to a node's attribute value.
  AttributeMatch(
    const std::string& attr_name,
    std::unique_ptr<ValueTest> value_test
  );

  /// Return a pair: First member is true if `node` has an attribute called
  /// `attr_name` whose value is passed by `value_test`, false otherwise.
  /// Second member is a pointer to the GumboAttribute that was matched,
  /// nullptr otherwise.
  MatchResult matches(const GumboNode * node) const final;

protected:
  /// The name of the html-node-attribute whose value is to be matched.
  const std::string attr_name_;
};


} // namespace hext


#endif // HEXT_PATTERN_ATTRIBUTE_MATCH_H_INCLUDED

