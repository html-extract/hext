#ifndef HEXT_MAKE_UNIQUE_H_INCLUDED
#define HEXT_MAKE_UNIQUE_H_INCLUDED

#include <memory>
#include <utility>


namespace hext {


/// Until C++14 is widely available, we ship our own version of make_unique.
template<typename T, typename ...Args>
std::unique_ptr<T> MakeUnique(Args&& ...args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


} // namespace hext


#endif // HEXT_MAKE_UNIQUE_H_INCLUDED

