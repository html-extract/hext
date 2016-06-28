# Download and build gtest. Gtest uses CMake.

INCLUDE(ExternalProject)
ExternalProject_Add(
    googletest
    URL https://github.com/google/googletest/archive/release-1.7.0.tar.gz
    URL_HASH SHA512=c623d5720c4ed574e95158529872815ecff478c03bdcee8b79c9b042a603533f93fe55f939bcfe2cd745ce340fd626ad6d9a95981596f1a4d05053d874cd1dfc
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

