#ifndef HEXT_OPTIONS_H_INCLUDED
#define HEXT_OPTIONS_H_INCLUDED


namespace hext {


/// Option flags to control extraction behaviour.
enum Option
{
  /// Default behaviour.
  Default       = 0,

  /// Do not remove invalid results.
  KeepInvalid   = 1 << 0,

  /// Do not force top level rules to be any descendant.
  NoAutoAnyDesc = 1 << 1
};

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

