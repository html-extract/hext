#ifndef HEXT_TEST_CONTAINS_ALL_WORDS_H_INCLUDED
#define HEXT_TEST_CONTAINS_ALL_WORDS_H_INCLUDED

#include "hext/test/ValueTest.h"
#include "hext/StringUtil.h"

#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>


namespace hext {
namespace test {


/// Check whether another string contains all given words. Word boundaries are
/// the beginning and end of subject, and spaces.
class ContainsAllWords : public ValueTest
{
public:
  explicit ContainsAllWords(std::string words)
  : words_()
  {
    boost::trim_if(words, boost::is_any_of(" "));
    boost::split(
      this->words_,
      words,
      boost::is_any_of(" "),
      boost::token_compress_on
    );
  }

  explicit ContainsAllWords(std::vector<std::string> words)
  : words_(std::move(words))
    {}

  /// Return true if subject contains all words.
  bool operator()(const char * subject) const final
  {
    if( !subject || this->words_.empty() )
      return false;

    std::string str_subject = subject;

    for(const auto& w : this->words_)
      if( !hext::ContainsWord(str_subject, w) )
        return false;

    return true;
  }

private:
  std::vector<std::string> words_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_CONTAINS_ALL_WORDS_H_INCLUDED

