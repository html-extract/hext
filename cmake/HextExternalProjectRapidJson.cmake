# Download rapidjson. Rapidjson is a header-only library.

INCLUDE(ExternalProject)
ExternalProject_Add(
    rapidjson
    URL https://github.com/miloyip/rapidjson/archive/v1.1.0.tar.gz
    URL_HASH SHA512=2e82a4bddcd6c4669541f5945c2d240fb1b4fdd6e239200246d3dd50ce98733f0a4f6d3daa56f865d8c88779c036099c52a9ae85d47ad263686b68a88d832dff
    TIMEOUT 10

    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""

    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

ExternalProject_Get_Property(rapidjson source_dir)

# Use rapidjson's include/ directory as an additional include directory
# Include as system headers to avoid warnings while compiling
INCLUDE_DIRECTORIES(SYSTEM ${source_dir}/include)

