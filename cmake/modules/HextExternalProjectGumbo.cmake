EXTERNALPROJECT_ADD(
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
EXTERNALPROJECT_GET_PROPERTY(gumbo source_dir)
INCLUDE_DIRECTORIES(${source_dir}/src)

# add gumbo's library directory when linking
EXTERNALPROJECT_GET_PROPERTY(gumbo binary_dir)
# LINK_DIRECTORIES will apply only to targets created after it is called
LINK_DIRECTORIES(${binary_dir}/.libs)

