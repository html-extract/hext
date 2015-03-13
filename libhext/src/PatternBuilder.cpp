#include "hext/PatternBuilder.h"


namespace hext {


PatternBuilder::PatternBuilder()
: bf_(nullptr)
, attr_name_()
, attr_literal_()
, attr_regex_()
, cap_var_()
, cap_regex_()
, mp_()
, cp_()
{
}

void PatternBuilder::consume_and_reset()
{
  if( this->cap_var_.size() )
    this->consume_capture_pattern();
  else
    this->consume_match_pattern();

  this->reset();
}

std::vector<std::unique_ptr<MatchPattern>>
PatternBuilder::get_matchp_and_reset()
{
  std::vector<std::unique_ptr<MatchPattern>> vec = std::move(this->mp_);

  this->reset();
  this->mp_.clear();

  return std::move(vec);
}

std::vector<std::unique_ptr<CapturePattern>>
PatternBuilder::get_capturep_and_reset()
{
  std::vector<std::unique_ptr<CapturePattern>> vec = std::move(this->cp_);

  this->reset();
  this->cp_.clear();

  return std::move(vec);
}

bool PatternBuilder::set_builtin_function(const std::string& bi)
{
  BuiltinFuncPtr func = GetBuiltinByName(bi);
  if( !func )
    return false;

  this->bf_ = func;
  return true;
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
  this->cap_regex_ = boost::regex(capture_regex);
}

void PatternBuilder::reset()
{
  this->bf_ = nullptr;
  this->attr_name_ = "";
  this->attr_literal_ = "";
  this->attr_regex_ = "";
  this->cap_var_ = "";
  this->cap_regex_ = boost::none;
}

void PatternBuilder::consume_match_pattern()
{
  std::unique_ptr<ValueTest> test;
  if( this->attr_regex_.size() )
    test = MakeUnique<RegexTest>(this->attr_regex_);
  else if( this->attr_literal_.size() )
    test = MakeUnique<LiteralTest>(this->attr_literal_);
  else
    test = MakeUnique<ValueTest>();

  std::unique_ptr<MatchPattern> p;
  if( this->bf_ )
    p = MakeUnique<BuiltinMatch>(this->bf_, std::move(test));
  else
    p = MakeUnique<AttributeMatch>(this->attr_name_, std::move(test));

  this->mp_.push_back(std::move(p));
}

void PatternBuilder::consume_capture_pattern()
{
  if( this->bf_ )
  {
    if( this->cap_regex_ )
      this->cp_.push_back(
        MakeUnique<BuiltinCapture>(
          this->cap_var_,
          this->bf_,
          this->cap_regex_.get()
        )
      );
    else
      this->cp_.push_back(
        MakeUnique<BuiltinCapture>(this->cap_var_, this->bf_)
      );
  }
  else
  {
    if( this->cap_regex_ )
      this->cp_.push_back(
        MakeUnique<AttributeCapture>(
          this->cap_var_, this->attr_name_, this->cap_regex_.get()
        )
      );
    else
      this->cp_.push_back(
        MakeUnique<AttributeCapture>(
          this->cap_var_, this->attr_name_
        )
      );

    this->mp_.push_back(
      MakeUnique<AttributeMatch>(this->attr_name_, MakeUnique<ValueTest>())
    );
  }
}


} // namespace hext

