# http://www.cmake.org/cmake/help/v3.0/module/FindPackageHandleStandardArgs.html

INCLUDE(FindPackageHandleStandardArgs)

FIND_PATH(Gumbo_INCLUDE_DIR gumbo.h)
FIND_LIBRARY(Gumbo_LIBRARY NAMES gumbo)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Gumbo DEFAULT_MSG Gumbo_LIBRARY Gumbo_INCLUDE_DIR)

