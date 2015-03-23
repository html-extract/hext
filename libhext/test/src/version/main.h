#include "hext/Version.h"


namespace {


TEST(Version, Exists)
{
  (void)hext::version_major;
  (void)hext::version_minor;
  (void)hext::version_git_sha1;
}


} // namespace

