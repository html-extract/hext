# Download latest rapidjson trunk. Rapidjson is a header-only library.

ExternalProject_Add(
    rapidjson
    GIT_REPOSITORY https://github.com/miloyip/rapidjson.git
    TIMEOUT 10

    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""

    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# Use rapidjson's include/ directory as an additional include directory
ExternalProject_Get_Property(rapidjson source_dir)

# Include as system headers to avoid warnings while compiling
INCLUDE_DIRECTORIES(SYSTEM ${source_dir}/include)

