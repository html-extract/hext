# Download rapidjson. Rapidjson is a header-only library.

INCLUDE(ExternalProject)
ExternalProject_Add(
    rapidjson
    URL https://github.com/miloyip/rapidjson/archive/v1.0.2.tar.gz
    URL_HASH SHA512=f5481d78773aca34d214b60e0da113779eba4af35b7c8fb4eddea5b3bda4e68cbe3fd06f698ee90f9e50c3fe985d327053f678c9fcc84339860c267b59313162
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

