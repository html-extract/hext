// Copyright 2015-2017 Thomas Trapp
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

#include "StringUtil.h"


namespace hext {


std::string TrimAndCollapseWs(std::string str)
{
  // To erase superfluous whitespace, shift all characters to the left,
  // replacing unwanted characters.

  // The end of the resulting string.
  std::string::size_type end = 0;
  // The index of the currently looked at character.
  std::string::size_type c = 0;
  // If we encounter any amount of whitespace, set need_space to true. A space
  // is only inserted if there is actually a non-whitespace character remaining
  // ("right trim").
  bool need_space = false;

  for(; c < str.size(); c++)
  {
    if( IsSpace(str[c]) )
    {
      // Do not insert a space if we are at the beginning of the
      // string ("left trim").
      if( end > 0 )
        need_space = true;
    }
    else
    {
      if( need_space )
      {
        // The current character is not whitespace and we have previously
        // encountered whitespace, so we need to prepend a space to the next
        // character.
        str[end++] = ' ';
        need_space = false;
      }
      str[end++] = str[c];
    }
  }

  // Erase all remaining characters.
  str.erase(end);
  return str;
}

bool IsSpace(char c) noexcept
{
  // http://www.w3.org/TR/html5/infrastructure.html#space-character
  // The space characters, for the purposes of this specification,
  // are U+0020 SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C),
  // and "CR" (U+000D).
  switch( c )
  {
    case ' ':
    case '\t':
    case '\n':
    case '\f':
    case '\r':
      return true;
    default:
      return false;
  }

  assert(false);
}

std::string CharName(char c)
{
  switch( c )
  {
    case '\n':
      return "[newline]";
    case '\t':
      return "[tab]";
    case '\r':
      return "[carriage-return]";
    case ' ':
      return "[space]";
    case '\0':
      return "[nullbyte]";
    default:
      break;
  }

  int ci = c;
  if( std::isprint(ci) )
    return std::string(1, c);
  else
    return std::string("[ascii: ") + std::to_string(ci) + "]";
}

CharPosPair CharPosition(const char * begin, const char * c) noexcept
{
  assert(begin && c && begin <= c);
  if( !begin || !c || c < begin )
    return CharPosPair(0, 0);

  // the position of the newline prior to c
  CharPosType line_offset = 0;

  // the line number of c
  CharPosType line_count = std::count(begin, c, '\n');

  if( line_count )
  {
    // find the position of the last newline
    auto last_line = std::find(std::reverse_iterator<const char *>(c),
                               std::reverse_iterator<const char *>(begin),
                               '\n');
    line_offset = std::distance(begin, last_line.base());
  }

  // the position of c in the overall input
  CharPosType char_offset = std::distance(begin, c);

  // the position of c in the current line
  CharPosType char_offset_in_line = char_offset - line_offset;

  return CharPosPair(line_count, char_offset_in_line);
}

int DecimalWidth(std::size_t number) noexcept
{
  int width = 1;
  while( number /= 10 )
    // overflow is impossible
    ++width;
  return width;
}

bool ContainsWord(std::string_view subject, std::string_view word) noexcept
{
  if( subject.empty() || word.empty() || word.size() > subject.size() )
    return false;

  std::string::size_type begin = 0;
  while( (begin = subject.find(word, begin)) != std::string::npos )
  {
    std::string::size_type end = begin + word.size();

    // Check if either at start of string or prefixed with space.
    bool start_is_bound = ( begin == 0 || subject[begin-1] == ' ' );

    // Check if either at end of string or suffixed with space.
    bool end_is_bound = ( end == subject.size() || subject[end] == ' ' );

    if( start_is_bound && end_is_bound )
      return true;

    begin = end;
  }

  return false;
}

void PrintNumberedLines(const char *  begin,
                        const char *  end,
                        std::ostream& out)
{
  assert(begin && end && begin <= end);
  if( !begin || !end || begin > end )
    return;

  boost::tokenizer<boost::char_separator<char>, const char *> lines(
      begin,
      end,
      // use keep_empty_tokens because we also have to print empty lines
      boost::char_separator<char>("\n", "", boost::keep_empty_tokens));

  std::size_t line_count = 1 + static_cast<std::size_t>(
      std::count(begin, end, '\n'));

  // Amount of digits needed to print the biggest line number
  int number_width = DecimalWidth(line_count);

  int line_num = 1;
  for(const auto& line : lines)
  {
    out << std::setw(number_width)
        << line_num++
        << ": "
        << line
        << '\n';
  }
}


} // namespace hext

