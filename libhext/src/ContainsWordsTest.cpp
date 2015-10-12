// Copyright 2015 Thomas Trapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "hext/ContainsWordsTest.h"

#include "StringUtil.h"

#include <utility>

#include <boost/algorithm/string.hpp>


namespace hext {


ContainsWordsTest::ContainsWordsTest(std::string words)
: words_()
{
  boost::trim_if(words, boost::is_any_of(" "));
  boost::split(this->words_,
               words,
               boost::is_any_of(" "),
               boost::token_compress_on);
}

ContainsWordsTest::ContainsWordsTest(std::vector<std::string> words) noexcept
: words_(std::move(words))  // noexcept
{
}

bool ContainsWordsTest::test(const char * subject) const
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

