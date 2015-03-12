#ifndef HEXT_OPTIONS_H_INCLUDED
#define HEXT_OPTIONS_H_INCLUDED


namespace hext {


/// Enum to allow for typesafe passing of options.
enum Option
{
  Default     = 0 << 0,
  KeepInvalid = 1 << 0
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


} // namespace hext


#endif // HEXT_OPTIONS_H_INCLUDED

