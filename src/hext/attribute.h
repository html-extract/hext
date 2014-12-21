#ifndef HEXT_ATTRIBUTE_H
#define HEXT_ATTRIBUTE_H

#include <string>


namespace hext {


class attribute
{
public:
  attribute()
  : name(""),
    value(""),
    capture(false),
    builtin(false)
  {
  }

  std::string get_name() const
  {
    return this->name;
  }

  std::string get_value() const
  {
    return this->value;
  }

  bool get_is_capture() const
  {
    return this->capture;
  }

  bool get_is_builtin() const
  {
    return this->builtin;
  }

  void set_name(const std::string& attribute_name)
  {
    this->name = attribute_name;
  }

  void set_value(const std::string& attribute_value)
  {
    this->value = attribute_value;
  }

  void set_is_capture(bool is_capture)
  {
    this->capture = is_capture;
  }

  void set_is_builtin(bool is_builtin)
  {
    this->builtin = is_builtin;
  }

private:
  std::string name;
  std::string value;
  bool capture;
  bool builtin;
};


} // namespace hext


#endif // HEXT_ATTRIBUTE_H

