# http://www.cmake.org/cmake/help/v3.0/module/FindPackageHandleStandardArgs.html

include(FindPackageHandleStandardArgs)

find_path(Gumbo_INCLUDE_DIR gumbo.h)
find_library(Gumbo_LIBRARY NAMES gumbo)

find_package_handle_standard_args(Gumbo DEFAULT_MSG Gumbo_LIBRARY Gumbo_INCLUDE_DIR)

