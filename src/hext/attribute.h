#ifndef HEXT_ATTRIBUTE_H
#define HEXT_ATTRIBUTE_H

#include <string>


namespace hext {


class attribute
{
public:
  attribute();

  std::string get_name() const;

  std::string get_value() const;

  bool get_is_capture() const;

  bool get_is_builtin() const;

  void set_name(const std::string& attribute_name);

  void set_value(const std::string& attribute_value);

  void set_is_capture(bool is_capture);

  void set_is_builtin(bool is_builtin);

private:
  std::string name;
  std::string value;
  bool capture;
  bool builtin;
};


} // namespace hext


#endif // HEXT_ATTRIBUTE_H

