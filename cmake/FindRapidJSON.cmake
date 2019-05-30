# http://www.cmake.org/cmake/help/v3.0/module/FindPackageHandleStandardArgs.html

include(FindPackageHandleStandardArgs)

find_path(RapidJSON_INCLUDE_DIRS rapidjson/rapidjson.h)

find_package_handle_standard_args(RapidJSON DEFAULT_MSG RapidJSON_INCLUDE_DIRS)

