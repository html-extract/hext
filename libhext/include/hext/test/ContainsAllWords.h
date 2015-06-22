#ifndef HEXT_TEST_CONTAINS_ALL_WORDS_H_INCLUDED
#define HEXT_TEST_CONTAINS_ALL_WORDS_H_INCLUDED

#include "hext/test/ValueTest.h"
#include "hext/StringUtil.h"

#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>


namespace hext {
namespace test {


/// ContainsAllWords is a ValueTest that checks whether another string contains
/// all given words. Word boundaries are the beginning and end of subject, and
/// spaces.
class ContainsAllWords : public ValueTest
{
public:
  explicit ContainsAllWords(std::string words);
  explicit ContainsAllWords(std::vector<std::string> words);

  /// Return true if subject contains all words.
  bool operator()(const char * subject) const final;

private:
  std::vector<std::string> words_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_CONTAINS_ALL_WORDS_H_INCLUDED

