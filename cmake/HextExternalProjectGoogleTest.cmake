# Download and build gtest. Gtest uses CMake.

INCLUDE(ExternalProject)
ExternalProject_Add(
    googletest
    URL https://github.com/google/googletest/archive/release-1.7.0.tar.gz
    TIMEOUT 10

    UPDATE_COMMAND ""
    INSTALL_COMMAND ""

    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# use googletest's include/ directory as an additional include directory
ExternalProject_Get_Property(googletest source_dir)
# Use SYSTEM to hide warnings.
INCLUDE_DIRECTORIES(SYSTEM ${source_dir}/include)

# add googletest's library directory when linking
ExternalProject_Get_Property(googletest binary_dir)
# LINK_DIRECTORIES will apply only to targets created after it is called
LINK_DIRECTORIES(${binary_dir})

