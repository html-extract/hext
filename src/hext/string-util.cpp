#include "hext/string-util.h"


namespace hext {


std::string TrimAndCollapseWs(std::string str)
{
  std::string::size_type i = 0;
  std::string::size_type c = 0;
  bool need_space = false;

  for(; c < str.size(); c++)
  {
    if( IsSpace(str[c]) )
    {
      if( i > 0 )
        need_space = true;
    }
    else
    {
      if( need_space )
      {
        str[i++] = ' ';
        need_space = false;
      }
      str[i++] = str[c];
    }
  }

  str.erase(i);
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
      int ci = c;
      return std::isprint(ci) ?
          // std::string has no constructor accepting char; abusing fill-constructor
          std::string(1, c)
        : std::string("[ascii: ") + std::to_string(ci) + "]";
  }

  assert(false);
  return "";
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
    boost::char_separator<char>("\n")
  );

  if( number_width < 1 )
    number_width = 1;

  unsigned int line_num = 1;
  for(const auto line : lines)
  {
    out << std::setw(number_width)
        << line_num++
        << ": "
        << line
        << '\n';
  }
}


} // namespace hext

