#include "htmlext/Version.h"


namespace htmlext {


const int version_major = 0;

const int version_minor = 1;

const char * version_git_sha1 = "7ed4ad7";

void PrintVersion(std::ostream& out)
{
  out << "html-extract v" << version_major << "." << version_minor
      << " build-" << version_git_sha1 << "\n";
}


} // namespace htmlext

