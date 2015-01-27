#ifndef HEXT_BUILTIN_CAPTURE_H
#define HEXT_BUILTIN_CAPTURE_H


#include <string>
#include <iostream>

#include <gumbo.h>

#include "hext/match-tree.h"
#include "hext/capture-pattern.h"
#include "hext/builtins.h"


namespace hext {


class builtin_capture : public capture_pattern
{
public:
  builtin_capture(
    const std::string& result_name,
    bi::builtin_func_ptr f,
    const std::string& regex
  );
  match_tree::name_value_pair capture(const GumboNode * node) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  const bi::builtin_func_ptr func;
};


} // namespace hext


#endif // HEXT_BUILTIN_CAPTURE_H

