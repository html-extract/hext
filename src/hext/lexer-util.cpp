#include "hext/lexer-util.h"


namespace hext {


std::string get_char_name(char c)
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
      return isprint(ci) ?
          // std::string has no constructor accepting char; abusing fill-constructor
          std::string(1, c)
        : std::string("[ascii: ") + std::to_string(ci) + "]";
  }

  assert(false);
  return "";
}

std::pair<size_t, size_t> get_char_position(
  const char * c,
  const char * begin,
  const char * end
)
{
  if(
    begin == nullptr ||
    c     == nullptr ||
    end   == nullptr ||
    // expect begin <= c <= end
    c      < begin   ||
    c      > end
  )
  {
    return std::pair<size_t, size_t>(0, 0);
  }

  // on empty input
  if( begin == end )
  {
    return std::pair<size_t, size_t>(0, 0);
  }

  // the position of the newline prior to c
  size_t line_offset = 0;
  // the line number of c
  size_t line_count = std::count(begin, c, '\n');

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
  size_t char_offset = std::distance(begin, c);
  // the position of c in the current line
  size_t char_offset_in_line = char_offset - line_offset;

  return std::pair<size_t, size_t>(
    line_count,
    char_offset_in_line
  );
}


} // namespace hext
