#include "hext/StringUtil.h"
#include "hext/test/ContainsWords.h"

#include <utility>

#include <boost/algorithm/string.hpp>


namespace hext {
namespace test {


ContainsWords::ContainsWords(std::string words)
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

ContainsWords::ContainsWords(std::vector<std::string> words)
: words_(std::move(words))
{
}

bool ContainsWords::operator()(const char * subject) const
{
  if( !subject || this->words_.empty() )
    return false;

  std::string str_subject = subject;

  for(const auto& w : this->words_)
    if( !hext::ContainsWord(str_subject, w) )
      return false;

  return true;
}


} // namespace test
} // namespace hext

