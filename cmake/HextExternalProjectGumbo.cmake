# Download gumbo's latest trunk and build it. Add gumbo's .lib/ directory
# to LINK_DIRECTORIES. Add gumbo's src/ directory to INCLUDE_DIRECTORIES.

INCLUDE(ExternalProject)
ExternalProject_Add(
    gumbo-parser
    URL https://github.com/google/gumbo-parser/archive/v0.10.1.tar.gz
    URL_HASH SHA512=bb1fb55cd07076ab6a9f38dc14db50397dbdca9a04ace4895dfba8b8cbc09038a96e26070c09c75fa929ada2e815affe233c1e2ecd8afe2aba6201647cf277d1
    TIMEOUT 10

    CONFIGURE_COMMAND ./autogen.sh COMMAND ./configure --prefix=${CMAKE_INSTALL_PREFIX}
    BUILD_COMMAND make
    INSTALL_COMMAND ""

    BUILD_IN_SOURCE ON)

# use gumbo's include/ directory as an additional include directory
ExternalProject_Get_Property(gumbo-parser source_dir)
SET(Gumbo_INCLUDE_DIR "${source_dir}/src" CACHE INTERNAL "")
INCLUDE_DIRECTORIES("${Gumbo_INCLUDE_DIR}")

# add gumbo's library directory when linking
ExternalProject_Get_Property(gumbo-parser binary_dir)
SET(Gumbo_PROJECT_DIR "${binary_dir}" CACHE INTERNAL "")
SET(Gumbo_LIBRARY_DIR "${binary_dir}/.libs" CACHE INTERNAL "")
# LINK_DIRECTORIES will apply only to targets created after it was called
LINK_DIRECTORIES(${binary_dir}/.libs)

