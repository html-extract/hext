#ifndef HEXT_OPTIONS_H_INCLUDED
#define HEXT_OPTIONS_H_INCLUDED


namespace hext {


/// Option flags to control extraction behaviour.
enum Option
{
  /// Default settings.
  Default       = 0 << 0,
  /// Do not remove invalid results.
  KeepInvalid   = 1 << 0,
  /// Do not force top level rules to be any descendant.
  NoAutoAnyDesc = 2 << 0
};

/// Bit operators to avoid having to cast to int.

inline Option operator|(Option left, Option right)
{
  return static_cast<Option>(static_cast<int>(left) | static_cast<int>(right));
}

inline Option operator&(Option left, Option right)
{
  return static_cast<Option>(static_cast<int>(left) & static_cast<int>(right));
}

inline Option operator^(Option left, Option right)
{
  return static_cast<Option>(static_cast<int>(left) ^ static_cast<int>(right));
}

inline Option operator~(Option opt)
{
  return static_cast<Option>(~static_cast<int>(opt));
}

inline Option& operator|=(Option& left, Option right)
{
  left = static_cast<Option>(static_cast<int>(left) | static_cast<int>(right));
  return left;
}

inline Option& operator&=(Option& left, Option right)
{
  left = static_cast<Option>(static_cast<int>(left) & static_cast<int>(right));
  return left;
}

inline Option& operator^=(Option& left, Option right)
{
  left = static_cast<Option>(static_cast<int>(left) ^ static_cast<int>(right));
  return left;
}


} // namespace hext


#endif // HEXT_OPTIONS_H_INCLUDED

