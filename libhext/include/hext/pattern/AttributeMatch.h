#ifndef HEXT_PATTERN_ATTRIBUTE_MATCH_H_INCLUDED
#define HEXT_PATTERN_ATTRIBUTE_MATCH_H_INCLUDED

#include "hext/MakeUnique.h"
#include "hext/test/ValueTest.h"
#include "hext/test/NotNull.h"
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
    std::string attr_name,
    std::unique_ptr<test::ValueTest> value_test = MakeUnique<test::NotNull>()
  );

  /// Return true if `node` has an attribute called `attr_name` whose value is
  /// passed by `value_test`, false otherwise.
  bool matches(const GumboNode * node) const final;

protected:
  /// The name of the html-node-attribute whose value is to be matched.
  std::string attr_name_;
};


} // namespace hext


#endif // HEXT_PATTERN_ATTRIBUTE_MATCH_H_INCLUDED

