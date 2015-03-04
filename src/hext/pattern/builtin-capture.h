#ifndef HEXT_PATTERN_BUILTIN_CAPTURE_H_INCLUDED
#define HEXT_PATTERN_BUILTIN_CAPTURE_H_INCLUDED

#include "hext/result-tree.h"
#include "hext/pattern/capture-pattern.h"
#include "hext/builtins.h"

#include <string>
#include <iostream>

#include <gumbo.h>
#include <boost/regex.hpp>


namespace hext {


/// A BuiltinCapture is a CapturePattern that captures the result of a builtin
/// function.
class BuiltinCapture : public CapturePattern
{
public:
  BuiltinCapture(
    const std::string& result_name,
    BuiltinFuncPtr f
  );
  BuiltinCapture(
    const std::string& result_name,
    BuiltinFuncPtr f,
    const boost::regex& regex
  );
  ResultTree::NameValuePair capture(const GumboNode * node) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  const BuiltinFuncPtr func_;
};


} // namespace hext


#endif // HEXT_PATTERN_BUILTIN_CAPTURE_H_INCLUDED

