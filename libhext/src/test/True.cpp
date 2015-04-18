#include "hext/test/True.h"


namespace hext {
namespace test {


bool True::operator()(const char * /* dummy */) const
{
  return true;
}


} // namespace test
} // namespace hext

