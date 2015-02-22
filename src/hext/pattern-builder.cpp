#include "hext/pattern-builder.h"


namespace hext {


PatternBuilder::PatternBuilder()
: bf(nullptr)
, attr_name()
, attr_literal()
, attr_regex()
, cap_var()
, cap_regex()
{
}

PatternBuilder::~PatternBuilder()
{
}

std::unique_ptr<MatchPattern> PatternBuilder::build_match_and_reset()
{
  std::unique_ptr<MatchPattern> p;
  std::unique_ptr<AttrTest> test;
  if( this->attr_regex.size() )
    test = make_unique<RegexText>(this->attr_regex);
  else
    test = make_unique<LiteralTest>(this->attr_literal);

  if( this->bf )
    p = make_unique<BuiltinMatch>(this->bf, std::move(test));
  else
    p = make_unique<AttributeMatch>(this->attr_name, std::move(test));

  this->reset();

  return std::move(p);
}

std::unique_ptr<CapturePattern> PatternBuilder::build_capture_and_reset()
{
  std::unique_ptr<CapturePattern> p;
  if( this->bf )
    p = make_unique<BuiltinCapture>(this->cap_var, this->bf, this->cap_regex);
  else
    p = make_unique<AttributeCapture>(
      this->cap_var, this->attr_name, this->cap_regex
    );

  this->reset();

  return std::move(p);
}

void PatternBuilder::reset()
{
  this->bf = nullptr;
  this->attr_name = "";
  this->attr_literal = "";
  this->attr_regex = "";
  this->cap_var = "";
  this->cap_regex = "";
}

void PatternBuilder::set_builtin_function(bi::BuiltinFuncPtr func)
{
  this->bf = func;
}

void PatternBuilder::set_attr_name(const std::string& attribute_name)
{
  this->attr_name = attribute_name;
}

void PatternBuilder::set_attr_literal(const std::string& attribute_literal)
{
  this->attr_literal = attribute_literal;
}

void PatternBuilder::set_attr_regex(const std::string& attribute_regex)
{
  this->attr_regex = attribute_regex;
}

void PatternBuilder::set_cap_var(const std::string& capture_var)
{
  this->cap_var = capture_var;
}

void PatternBuilder::set_cap_regex(const std::string& capture_regex)
{
  this->cap_regex = capture_regex;
}


} // namespace hext

