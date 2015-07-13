#ifndef HEXT_CONTAINS_WORDS_TEST_H_INCLUDED
#define HEXT_CONTAINS_WORDS_TEST_H_INCLUDED

#include "hext/ValueTest.h"

#include <string>
#include <vector>


namespace hext {


/// Test whether another string contains all given words. Word boundaries are
/// the beginning and end of subject, and spaces.
class ContainsWordsTest : public ValueTest
{
public:
  explicit ContainsWordsTest(std::string words);
  explicit ContainsWordsTest(std::vector<std::string> words);

  /// Return true if subject contains all words.
  bool test(const char * subject) const final;

private:
  std::vector<std::string> words_;
};


} // namespace hext


#endif // HEXT_CONTAINS_WORDS_TEST_H_INCLUDED

