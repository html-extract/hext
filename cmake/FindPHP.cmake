# http://www.cmake.org/cmake/help/v3.0/module/FindPackageHandleStandardArgs.html

# Find PHP using php-config.
# Sets PHP_INCLUDE_DIRS if successful.

include(CMakeFindFrameworks)
include(FindPackageHandleStandardArgs)

find_program(PHP_CONFIG NAMES "php-config")

if(PHP_CONFIG)
  execute_process(
    COMMAND ${PHP_CONFIG} "--includes"
    OUTPUT_VARIABLE PHP_INCLUDE_DIRS)
  string(REPLACE "\n" "" PHP_INCLUDE_DIRS "${PHP_INCLUDE_DIRS}")
  string(REPLACE "-I" ";" PHP_INCLUDE_DIRS "${PHP_INCLUDE_DIRS}")
  execute_process(
    COMMAND ${PHP_CONFIG} "--version"
    OUTPUT_VARIABLE PHP_VERSION)
endif()

find_package_handle_standard_args(Php DEFAULT_MSG PHP_INCLUDE_DIRS)

