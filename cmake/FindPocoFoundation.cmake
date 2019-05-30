# http://www.cmake.org/cmake/help/v3.0/module/FindPackageHandleStandardArgs.html

include(FindPackageHandleStandardArgs)

find_path(PocoFoundation_INCLUDE_DIR Poco/Foundation.h)
find_library(PocoFoundation_LIBRARY NAMES PocoFoundation)

find_package_handle_standard_args(PocoFoundation DEFAULT_MSG PocoFoundation_LIBRARY PocoFoundation_INCLUDE_DIR)

