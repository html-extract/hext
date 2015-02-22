#include "hext/pattern-builder.h"


namespace hext {


PatternBuilder::PatternBuilder()
: bf_(nullptr)
, attr_name_()
, attr_literal_()
, attr_regex_()
, cap_var_()
, cap_regex_()
{
}

PatternBuilder::~PatternBuilder()
{
}

std::unique_ptr<MatchPattern> PatternBuilder::build_match_and_reset()
{
  std::unique_ptr<MatchPattern> p;
  std::unique_ptr<AttrTest> test;
  if( this->attr_regex_.size() )
    test = make_unique<RegexText>(this->attr_regex_);
  else
    test = make_unique<LiteralTest>(this->attr_literal_);

  if( this->bf_ )
    p = make_unique<BuiltinMatch>(this->bf_, std::move(test));
  else
    p = make_unique<AttributeMatch>(this->attr_name_, std::move(test));

  this->reset();

  return std::move(p);
}

std::unique_ptr<CapturePattern> PatternBuilder::build_capture_and_reset()
{
  std::unique_ptr<CapturePattern> p;
  if( this->bf_ )
    p = make_unique<BuiltinCapture>(this->cap_var_, this->bf_, this->cap_regex_);
  else
    p = make_unique<AttributeCapture>(
      this->cap_var_, this->attr_name_, this->cap_regex_
    );

  this->reset();

  return std::move(p);
}

void PatternBuilder::reset()
{
  this->bf_ = nullptr;
  this->attr_name_ = "";
  this->attr_literal_ = "";
  this->attr_regex_ = "";
  this->cap_var_ = "";
  this->cap_regex_ = "";
}

void PatternBuilder::set_builtin_function(bi::BuiltinFuncPtr func)
{
  this->bf_ = func;
}

void PatternBuilder::set_attr_name(const std::string& attribute_name)
{
  this->attr_name_ = attribute_name;
}

void PatternBuilder::set_attr_literal(const std::string& attribute_literal)
{
  this->attr_literal_ = attribute_literal;
}

void PatternBuilder::set_attr_regex(const std::string& attribute_regex)
{
  this->attr_regex_ = attribute_regex;
}

void PatternBuilder::set_cap_var(const std::string& capture_var)
{
  this->cap_var_ = capture_var;
}

void PatternBuilder::set_cap_regex(const std::string& capture_regex)
{
  this->cap_regex_ = capture_regex;
}


} // namespace hext

