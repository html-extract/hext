#include "hext/test/True.h"


namespace hext {
namespace test {


bool True::operator()(const char * subject) const
{
  return subject != nullptr;
}


} // namespace test
} // namespace hext

