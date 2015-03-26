#ifndef HEXT_PATTERN_CONTAINS_WORD_TEST_H_INCLUDED
#define HEXT_PATTERN_CONTAINS_WORD_TEST_H_INCLUDED

#include "hext/pattern/ValueTest.h"

#include <string>


namespace hext {


/// A ContainsWordTest is a ValueTest that checks whether another string
/// contains a word given as literal. Word boundaries are the beginning and end
/// of subject, and spaces.
class ContainsWordTest : public ValueTest
{
public:
  explicit ContainsWordTest(std::string literal);

  /// Return true if subject contains literal as a word.
  bool test(const char * subject) const final;

private:
  const std::string lit_;
};


} // namespace hext


#endif // HEXT_PATTERN_CONTAINS_WORD_TEST_H_INCLUDED

