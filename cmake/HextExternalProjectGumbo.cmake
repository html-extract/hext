# Download gumbo's latest trunk and build it. Add gumbo's .lib/ directory
# to LINK_DIRECTORIES. Add gumbo's src/ directory to INCLUDE_DIRECTORIES.

INCLUDE(ExternalProject)
ExternalProject_Add(
    gumbo
    GIT_REPOSITORY https://github.com/google/gumbo-parser.git
    TIMEOUT 10

    CONFIGURE_COMMAND ./autogen.sh COMMAND ./configure --prefix=${CMAKE_BINARY_DIR}
    BUILD_COMMAND make
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""

    BUILD_IN_SOURCE ON
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# use gumbo's include/ directory as an additional include directory
ExternalProject_Get_Property(gumbo source_dir)
INCLUDE_DIRECTORIES(${source_dir}/src)

# add gumbo's library directory when linking
ExternalProject_Get_Property(gumbo binary_dir)
# LINK_DIRECTORIES will apply only to targets created after it is called
LINK_DIRECTORIES(${binary_dir}/.libs)

