#ifndef HEXT_OPTIONS_H_INCLUDED
#define HEXT_OPTIONS_H_INCLUDED


namespace hext {


/// Option flags to control extraction behaviour.
enum Option
{
  /// No options.
  NoOption            = 0,

  /// Insert an AttributeMatch for every AttributeCapture.
  CapAttribMustExist  = 1 << 2,
};

/// Default options.
constexpr const Option DefaultOption = static_cast<Option>(
  Option::CapAttribMustExist
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

