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
    capture(false)
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

  bool is_capture() const
  {
    return this->capture;
  }

  void set_name(std::string attribute_name)
  {
    this->name = attribute_name;
  }

  void get_value(std::string attribute_value)
  {
    this->value = attribute_value;
  }

  void set_is_capture(bool is_capture)
  {
    this->capture = is_capture;
  }

private:
  std::string name;
  std::string value;
  bool capture;
};


} // namespace hext


#endif // HEXT_ATTRIBUTE_H

