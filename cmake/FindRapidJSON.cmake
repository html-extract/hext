# http://www.cmake.org/cmake/help/v3.0/module/FindPackageHandleStandardArgs.html

INCLUDE(FindPackageHandleStandardArgs)

FIND_PATH(RapidJSON_INCLUDE_DIRS rapidjson/rapidjson.h)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(RapidJSON DEFAULT_MSG RapidJSON_INCLUDE_DIRS)

