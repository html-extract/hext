# http://www.cmake.org/cmake/help/v3.0/module/FindPackageHandleStandardArgs.html

INCLUDE(FindPackageHandleStandardArgs)

FIND_PATH(GUMBO_INCLUDE_DIR gumbo.h)
FIND_LIBRARY(GUMBO_LIBRARY NAMES gumbo)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(libgumbo DEFAULT_MSG GUMBO_LIBRARY GUMBO_INCLUDE_DIR)

