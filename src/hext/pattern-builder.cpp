#include "hext/pattern-builder.h"


namespace hext {


pattern_builder::pattern_builder()
: bf(nullptr)
, attr_name()
, attr_literal()
, attr_regex()
, cap_var()
, cap_regex()
{
}

pattern_builder::~pattern_builder()
{
}

std::unique_ptr<match_pattern> pattern_builder::build_match_and_reset()
{
  std::unique_ptr<match_pattern> p;
  std::unique_ptr<attr_test> test;
  if( this->attr_regex.size() )
    test = make_unique<regex_test>(this->attr_regex);
  else
    test = make_unique<literal_test>(this->attr_literal);

  if( this->bf )
    p = make_unique<builtin_match>(this->bf, std::move(test));
  else
    p = make_unique<attribute_match>(this->attr_name, std::move(test));

  this->reset();

  return std::move(p);
}

std::unique_ptr<capture_pattern> pattern_builder::build_capture_and_reset()
{
  std::unique_ptr<capture_pattern> p;
  if( this->bf )
    p = make_unique<builtin_capture>(this->cap_var, this->bf, this->cap_regex);
  else
    p = make_unique<attribute_capture>(
      this->cap_var, this->attr_name, this->cap_regex
    );

  this->reset();

  return std::move(p);
}

void pattern_builder::reset()
{
  this->bf = nullptr;
  this->attr_name = "";
  this->attr_literal = "";
  this->attr_regex = "";
  this->cap_var = "";
  this->cap_regex = "";
}

void pattern_builder::set_builtin_function(bi::builtin_func_ptr func)
{
  this->bf = func;
}

void pattern_builder::set_attr_name(const std::string& attribute_name)
{
  this->attr_name = attribute_name;
}

void pattern_builder::set_attr_literal(const std::string& attribute_literal)
{
  this->attr_literal = attribute_literal;
}

void pattern_builder::set_attr_regex(const std::string& attribute_regex)
{
  this->attr_regex = attribute_regex;
}

void pattern_builder::set_cap_var(const std::string& capture_var)
{
  this->cap_var = capture_var;
}

void pattern_builder::set_cap_regex(const std::string& capture_regex)
{
  this->cap_regex = capture_regex;
}


} // namespace hext

