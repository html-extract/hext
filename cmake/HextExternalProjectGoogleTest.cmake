# Download and build gtest. Gtest uses CMake.

INCLUDE(ExternalProject)
ExternalProject_Add(
    googletest
    URL http://googletest.googlecode.com/files/gtest-1.7.0.zip
    TIMEOUT 10

    UPDATE_COMMAND ""
    INSTALL_COMMAND ""

    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# use googletest's include/ directory as an additional include directory
ExternalProject_Get_Property(googletest source_dir)
INCLUDE_DIRECTORIES(${source_dir}/include)

# add googletest's library directory when linking
ExternalProject_Get_Property(googletest binary_dir)
# LINK_DIRECTORIES will apply only to targets created after it is called
LINK_DIRECTORIES(${binary_dir})

