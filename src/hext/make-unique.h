#ifndef HEXT_MAKE_UNIQUE_H
#define HEXT_MAKE_UNIQUE_H

#include <memory>
#include <utility>


namespace hext {


template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


} // namespace hext


#endif // HEXT_MAKE_UNIQUE_H

