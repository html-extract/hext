#ifndef HTMLEXT_VERSION_H_INCLUDED
#define HTMLEXT_VERSION_H_INCLUDED

#include "hext/Version.h"

#include <iostream>


namespace htmlext {


/// Major version numer.
extern const int version_major;

/// Minor version number.
extern const int version_minor;

/// Git SHA-1 of this build.
extern const char * version_git_sha1;

/// Print version to out.
void PrintVersion(std::ostream& out = std::cout);


} // namespace htmlext


#endif // HTMLEXT_VERSION_H_INCLUDED

