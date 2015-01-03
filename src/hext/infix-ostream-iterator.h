#ifndef HEXT_INFIX_OSTREAM_ITERATOR_H
#define HEXT_INFIX_OSTREAM_ITERATOR_H

#include <cassert>
#include <string>
#include <ostream>
#include <iterator>


namespace hext {


template<
  typename T,
  typename char_t = char,
  typename traits = std::char_traits<char_t>
>
class infix_ostream_iterator
{
public:
  // std::iterator typedefs (avoid inheriting from std::iterator)
  typedef std::output_iterator_tag iterator_category;
  typedef void value_type;
  typedef void difference_type;
  typedef void pointer;
  typedef void reference;

  // std::ostream_iterator typedefs
  typedef char_t char_type;
  typedef traits traits_type;
  typedef std::basic_ostream<char_t, traits> ostream_type;

  infix_ostream_iterator(ostream_type& s)
  : stream(&s),
    delimiter(nullptr),
    is_first(true)
  {
  }

  infix_ostream_iterator(ostream_type& s, const char_type * delim)
  : stream(&s),
    delimiter(delim),
    is_first(true)
  {
  }

  infix_ostream_iterator(const infix_ostream_iterator& obj)
  : stream(obj.stream),
    delimiter(obj.delimiter),
    is_first(obj.is_first)
  {
  }

  infix_ostream_iterator<T, char_t, traits>&
  operator=(const T& value)
  {
    assert(this->stream != nullptr);

    if( this->is_first )
      this->is_first = false;
    else if( this->delimiter )
      *this->stream << this->delimiter;

    *this->stream << value;

    return *this;
  }

  infix_ostream_iterator<T, char_t, traits>&
  operator*()
  {
    return *this;
  }

  infix_ostream_iterator<T, char_t, traits>&
  operator++()
  {
    return *this;
  }

  infix_ostream_iterator<T, char_t, traits>&
  operator++(int)
  {
    return *this;
  }

private:
  ostream_type * stream;
  const char_type * delimiter; 
  bool is_first;
};


} // namespace hext


#endif // HEXT_INFIX_OSTREAM_ITERATOR_H

