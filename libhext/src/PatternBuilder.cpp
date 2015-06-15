#include "hext/PatternBuilder.h"


namespace hext {


PatternBuilder::PatternBuilder()
: bf_(nullptr)
, optional_(false)
, negate_(false)
, attr_name_()
, attr_literal_()
, cap_var_()
, regex_str_()
, regex_()
, regex_opt_(boost::regex::perl)
, nth_multiplier_(0)
, nth_addend_(-1)
, literal_operator_('0')
, mp_()
, cp_()
{
}

void PatternBuilder::consume_pattern()
{
  if( this->cap_var_.size() )
    this->consume_capture_pattern();
  else
    this->consume_match_pattern();

  this->reset();
}

std::vector<std::unique_ptr<MatchPattern>>
PatternBuilder::take_match_patterns()
{
  std::vector<std::unique_ptr<MatchPattern>> vec = std::move(this->mp_);

  this->reset();
  this->mp_.clear();

  return std::move(vec);
}

std::vector<std::unique_ptr<CapturePattern>>
PatternBuilder::take_capture_patterns()
{
  std::vector<std::unique_ptr<CapturePattern>> vec = std::move(this->cp_);

  this->reset();
  this->cp_.clear();

  return std::move(vec);
}

void PatternBuilder::consume_nth_child(
  NthChildMatch::OffsetOf offset_of,
  GumboTag count_tag
)
{
  // If nth_addend_ hasn't been set yet, use nth_multiplier_ as the shift
  // argument to NthChildMatch. This makes lexing easier.
  if( this->nth_addend_ < 0 )
  {
    this->mp_.push_back(
      MakeUnique<NthChildMatch>(
        0,
        this->nth_multiplier_,
        count_tag,
        offset_of
      )
    );
  }
  else
  {
    this->mp_.push_back(
      MakeUnique<NthChildMatch>(
        this->nth_multiplier_,
        this->nth_addend_,
        count_tag,
        offset_of
      )
    );
  }

  this->nth_multiplier_ = 0;
  this->nth_addend_ = -1;
}

bool PatternBuilder::set_builtin(const std::string& bi)
{
  BuiltinFuncPtr func = GetBuiltinByName(bi);
  if( !func )
    return false;

  this->bf_ = func;
  return true;
}

void PatternBuilder::set_optional()
{
  this->optional_ = true;
}

void PatternBuilder::set_negate()
{
  this->negate_ = true;
}

void PatternBuilder::set_attr_name(const std::string& attribute_name)
{
  this->attr_name_ = attribute_name;
}

void PatternBuilder::set_attr_literal(const std::string& attribute_literal)
{
  this->attr_literal_ = attribute_literal;
}

std::string::size_type PatternBuilder::regex_length() const
{
  return this->regex_str_.size();
}

void PatternBuilder::set_regex_str(const std::string& regex)
{
  this->regex_str_ = regex;
}

bool PatternBuilder::set_regex_mod(const std::string& regex_mod)
{
  for(const auto c : regex_mod)
  {
    switch( c )
    {
      case 'i':
        this->regex_opt_ |= boost::regex::icase;
        break;
      case 'c':
        this->regex_opt_ |= boost::regex::collate;
        break;
      default:
        return false;
    }
  }

  return true;
}

void PatternBuilder::consume_regex()
{
  this->regex_ = boost::regex(this->regex_str_, this->regex_opt_);
}

void PatternBuilder::set_cap_var(const std::string& capture_var)
{
  this->cap_var_ = capture_var;
}

void PatternBuilder::set_nth_mul(int multiplier)
{
  this->nth_multiplier_ = multiplier;
}

void PatternBuilder::set_nth_add(int addend)
{
  this->nth_addend_ = addend;
}

void PatternBuilder::set_literal_op(char op)
{
  this->literal_operator_ = op;
}

void PatternBuilder::reset()
{
  this->bf_ = nullptr;
  this->optional_ = false;
  this->negate_ = false;
  this->attr_name_ = "";
  this->attr_literal_ = "";
  this->cap_var_ = "";
  this->regex_str_ = "";
  this->regex_ = boost::none;
  this->regex_opt_ = boost::regex::perl;
  this->nth_multiplier_ = 0;
  this->nth_addend_ = -1;
  this->literal_operator_ = '0';
}

void PatternBuilder::consume_match_pattern()
{
  std::unique_ptr<test::ValueTest> test;

  if( this->literal_operator_ != '0' )
  {
    switch(this->literal_operator_)
    {
      case '^':
        test = MakeUnique<test::BeginsWith>(this->attr_literal_);
        break;
      case '*':
        test = MakeUnique<test::Contains>(this->attr_literal_);
        break;
      case '~':
        test = MakeUnique<test::ContainsWord>(this->attr_literal_);
        break;
      case '$':
        test = MakeUnique<test::EndsWith>(this->attr_literal_);
        break;
      default:
        test = MakeUnique<test::Equals>(this->attr_literal_);
        break;
    }
  }
  else if( this->regex_ )
  {
    test = MakeUnique<test::Regex>(this->regex_.get());
  }
  else if( this->attr_literal_.size() )
  {
    test = MakeUnique<test::Equals>(this->attr_literal_);
  }
  else
  {
    test = MakeUnique<test::True>();
  }

  if( this->negate_ )
  {
    test = MakeUnique<test::NegateValueTest>(std::move(test));
  }

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
    this->cp_.push_back(
      MakeUnique<BuiltinCapture>(
        this->cap_var_,
        this->bf_,
        this->regex_
      )
    );
  }
  else
  {
    this->cp_.push_back(
      MakeUnique<AttributeCapture>(
        this->cap_var_, this->attr_name_, this->regex_
      )
    );

    if( !this->optional_ )
      this->mp_.push_back(
        MakeUnique<AttributeMatch>(this->attr_name_, MakeUnique<test::True>())
      );
  }
}


} // namespace hext

