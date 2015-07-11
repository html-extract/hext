#include "hext/StringUtil.h"
#include "hext/ContainsWordsTest.h"

#include <utility>

#include <boost/algorithm/string.hpp>


namespace hext {


ContainsWordsTest::ContainsWordsTest(std::string words)
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

ContainsWordsTest::ContainsWordsTest(std::vector<std::string> words)
: words_(std::move(words))
{
}

bool ContainsWordsTest::operator()(const char * subject) const
{
  if( !subject || this->words_.empty() )
    return false;

  std::string str_subject = subject;

  for(const auto& w : this->words_)
    if( !hext::ContainsWord(str_subject, w) )
      return false;

  return true;
}


} // namespace hext

