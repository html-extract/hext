#include "hext/test/NotNull.h"


namespace hext {
namespace test {


bool NotNull::operator()(const char * subject) const
{
  return subject != nullptr;
}


} // namespace test
} // namespace hext

