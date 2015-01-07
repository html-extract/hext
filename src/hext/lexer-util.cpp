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

char_pos_pair get_char_position(
  const char * c,
  const char * begin,
  const char * end
)
{
  if( !begin || !c || !end )
    return char_pos_pair(0, 0);

  // expect c to be within range begin to end
  if( c < begin || c >= end || begin == end )
    return char_pos_pair(0, 0);

  // the position of the newline prior to c
  char_pos_type line_offset = 0;
  // the line number of c
  char_pos_type line_count = std::count(begin, c, '\n');

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
  char_pos_type char_offset = std::distance(begin, c);
  // the position of c in the current line
  char_pos_type char_offset_in_line = char_offset - line_offset;

  return char_pos_pair(line_count, char_offset_in_line);
}


} // namespace hext

