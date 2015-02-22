#ifndef HEXT_PATTERN_BUILDER_H
#define HEXT_PATTERN_BUILDER_H

#include <string>
#include <memory>

#include "hext/make-unique.h"
#include "hext/builtins.h"
#include "hext/pattern/attr-test.h"
#include "hext/pattern/literal-test.h"
#include "hext/pattern/regex-test.h"
#include "hext/pattern/match-pattern.h"
#include "hext/pattern/capture-pattern.h"
#include "hext/pattern/attribute-match.h"
#include "hext/pattern/builtin-match.h"
#include "hext/pattern/attribute-capture.h"
#include "hext/pattern/builtin-capture.h"


namespace hext {


class PatternBuilder
{
public:
  PatternBuilder();
  ~PatternBuilder();
  std::unique_ptr<MatchPattern> build_match_and_reset();
  std::unique_ptr<CapturePattern> build_capture_and_reset();
  void reset();

  void set_builtin_function(bi::BuiltinFuncPtr func);
  void set_attr_name(const std::string& attribute_name);
  void set_attr_literal(const std::string& attribute_literal);
  void set_attr_regex(const std::string& attribute_regex);
  void set_cap_var(const std::string& capture_var);
  void set_cap_regex(const std::string& capture_regex);

private:
  bi::BuiltinFuncPtr bf;
  std::string attr_name;
  std::string attr_literal;
  std::string attr_regex;
  std::string cap_var;
  std::string cap_regex;
};


} // namespace hext


#endif // HEXT_PATTERN_BUILDER_H

