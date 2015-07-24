#ifndef HEXT_VERSION_H_INCLUDED
#define HEXT_VERSION_H_INCLUDED

/// @file
///   Version numbers.


namespace hext {


/// Major version number.
extern const int version_major;

/// Minor version number.
extern const int version_minor;

/// Patch version number.
extern const int version_patch;

/// Git SHA-1 of this build.
extern const char * version_git_sha1;


} // namespace hext


#endif // HEXT_VERSION_H_INCLUDED

