#ifndef HEXT_OPTIONS_H_INCLUDED
#define HEXT_OPTIONS_H_INCLUDED


namespace hext {


/// Option flags to control extraction behaviour.
enum Option
{
  /// No options.
  NoOption            = 0,

  /// Remove incomplete ResultTree branches.
  RemoveIncomplete    = 1 << 0,

  /// Force top level rules to be any descendant.
  ForceTopRuleAnyDesc = 1 << 1,

  /// Insert an AttributeMatch for every AttributeCapture.
  CapAttribMustExist  = 1 << 2,

  /// After capturing values, interleave the results from all top level rules.
  InterleaveResults   = 1 << 3
};

/// Default options.
constexpr const Option DefaultOption = static_cast<Option>(
    Option::RemoveIncomplete
  | Option::ForceTopRuleAnyDesc
  | Option::CapAttribMustExist
  | Option::InterleaveResults
);

/// Option OR.
inline Option operator|(Option left, Option right)
{
  return static_cast<Option>(static_cast<int>(left) | static_cast<int>(right));
}

/// Option AND.
inline Option operator&(Option left, Option right)
{
  return static_cast<Option>(static_cast<int>(left) & static_cast<int>(right));
}

/// Option XOR.
inline Option operator^(Option left, Option right)
{
  return static_cast<Option>(static_cast<int>(left) ^ static_cast<int>(right));
}

/// Option NOT.
inline Option operator~(Option opt)
{
  return static_cast<Option>(~static_cast<int>(opt));
}

/// Option OR-assignment.
inline Option& operator|=(Option& left, Option right)
{
  left = static_cast<Option>(static_cast<int>(left) | static_cast<int>(right));
  return left;
}

/// Option AND-assignment.
inline Option& operator&=(Option& left, Option right)
{
  left = static_cast<Option>(static_cast<int>(left) & static_cast<int>(right));
  return left;
}

/// Option XOR-assignment.
inline Option& operator^=(Option& left, Option right)
{
  left = static_cast<Option>(static_cast<int>(left) ^ static_cast<int>(right));
  return left;
}


} // namespace hext


#endif // HEXT_OPTIONS_H_INCLUDED

