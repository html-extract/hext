#ifndef HEXT_PRINT_H
#define HEXT_PRINT_H

#include <iostream>
#include <string>
#include <algorithm>

#include "hext/rule.h"
#include "hext/attribute.h"


namespace hext {


void print_rule(rule r, unsigned int indent_level = 0, std::ostream& out = std::cout)
{
  unsigned int cap_limit = r.get_capture_limit();

  out << ( indent_level ? std::string(indent_level * 2, ' ') : "" )
      << "<"
      << ( r.get_is_direct_descendant() ? "!" : "" )
      << ( cap_limit > 0 ? ( cap_limit > 1 ? std::to_string(cap_limit) : "" ) : "*" )
      << r.get_tag_name()
      << " ";

  std::for_each(r.attributes_begin(), r.attributes_end(), [&out](attribute a) { 
    out << a.get_name() 
        << "=\""
        << ( a.get_is_capture() ? "(:" : "" )
        << a.get_value()
        << ( a.get_is_capture() ? ")" : "" )
        << "\" ";
  });

  out << ">\n";
  std::for_each(r.children_begin(), r.children_end(), [indent_level, &out](rule c) {
    print_rule(c, indent_level + 1, out);
  });
}


}


#endif // HEXT_PRINT_H

