# http://www.cmake.org/cmake/help/v3.0/module/FindPackageHandleStandardArgs.html

INCLUDE(FindPackageHandleStandardArgs)

FIND_PATH(PocoFoundation_INCLUDE_DIR Poco/Foundation.h)
FIND_LIBRARY(PocoFoundation_LIBRARY NAMES PocoFoundation)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(PocoFoundation DEFAULT_MSG PocoFoundation_LIBRARY PocoFoundation_INCLUDE_DIR)

