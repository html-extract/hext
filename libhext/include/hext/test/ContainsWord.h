#ifndef HEXT_TEST_CONTAINS_WORD_H_INCLUDED
#define HEXT_TEST_CONTAINS_WORD_H_INCLUDED

#include "hext/StringUtil.h"
#include "hext/test/ValueTest.h"

#include <string>


namespace hext {
namespace test {


/// ContainsWord is a ValueTest that checks whether another string contains a
/// word given as literal. Word boundaries are the beginning and end of
/// subject, and spaces.
class ContainsWord : public ValueTest
{
public:
  explicit ContainsWord(std::string literal);

  /// Return true if subject contains literal as a word.
  bool operator()(const char * subject) const final;

private:
  std::string lit_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_CONTAINS_WORD_H_INCLUDED

