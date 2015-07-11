#ifndef HEXT_TEST_CONTAINS_WORDS_H_INCLUDED
#define HEXT_TEST_CONTAINS_WORDS_H_INCLUDED

#include "hext/test/ValueTest.h"

#include <string>
#include <vector>


namespace hext {
namespace test {


/// Test whether another string contains all given words. Word boundaries are
/// the beginning and end of subject, and spaces.
class ContainsWords : public ValueTest
{
public:
  explicit ContainsWords(std::string words);
  explicit ContainsWords(std::vector<std::string> words);

  /// Return true if subject contains all words.
  bool operator()(const char * subject) const final;

private:
  std::vector<std::string> words_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_CONTAINS_WORDS_H_INCLUDED

