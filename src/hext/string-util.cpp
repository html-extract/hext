#include "hext/string-util.h"


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

bool IsSpace(char c)
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

  return false;
}

std::string GetCharName(char c)
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

CharPosPair GetCharPosition(
  const char * c,
  const char * begin,
  const char * end
)
{
  if( !begin || !c || !end )
    return CharPosPair(0, 0);

  // expect c to be within range begin to end
  if( c < begin || c > end || begin == end )
    return CharPosPair(0, 0);

  // the position of the newline prior to c
  CharPosType line_offset = 0;
  // the line number of c
  CharPosType line_count = std::count(begin, c, '\n');

  if( line_count )
  {
    // find the position of the last newline
    std::reverse_iterator<const char *> last_line = std::find(
      std::reverse_iterator<const char *>(c),
      std::reverse_iterator<const char *>(begin),
      '\n'
    );
    line_offset = std::distance(begin, last_line.base());
  }

  // the position of c in the overall input
  CharPosType char_offset = std::distance(begin, c);
  // the position of c in the current line
  CharPosType char_offset_in_line = char_offset - line_offset;

  return CharPosPair(line_count, char_offset_in_line);
}

int GetDecNumberWidth(ptrdiff_t number)
{
  number = std::abs(number);
  int number_width = 1;
  while( (number /= 10) > 0 )
    number_width++;
  return number_width;
}

void PrintWithLineNumbers(
  const char * begin,
  const char * end,
  int number_width,
  std::ostream& out
)
{
  if( !begin || !end )
    return;

  boost::tokenizer<boost::char_separator<char>, const char *> lines(
    begin,
    end,
    // keep_empty_tokens is neccessary because we also have to print empty lines
    boost::char_separator<char>("\n", "", boost::keep_empty_tokens)
  );

  if( number_width < 1 )
    number_width = 1;

  unsigned int line_num = 1;
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

