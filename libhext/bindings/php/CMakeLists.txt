###### HEXT-PHP ################################################################
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

# https://cmake.org/cmake/help/latest/policy/CMP0167.html
# Prefer Boost-installed cmake configuration for package Boost.
if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

project(hext-php)

# Add the top-level cmake module directory to CMAKE_MODULE_PATH
list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/../../../cmake)

# Set required C++ standard or abort.
include(HextForceCppStd)

# If build type was not specified, build Release.
include(HextDefaultBuildRelease)


###### DEPENDENCIES ############################################################

### SWIG
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

### PHP
find_package(PHP REQUIRED)
if(PHP_VERSION VERSION_LESS "7.0.0")
  message(FATAL_ERROR "PHP7.0 or later required")
endif()

### LIBHEXT
find_package(Hext REQUIRED)

### WRAPPERS
include_directories("${PROJECT_SOURCE_DIR}/..")


###### PHP #####################################################################
include_directories(SYSTEM ${PHP_INCLUDE_DIRS})

set_source_files_properties(
  "${PROJECT_SOURCE_DIR}/phphext.i" PROPERTIES CPLUSPLUS ON)
swig_add_library(
  phphext
  LANGUAGE php7
  SOURCES
  "${PROJECT_SOURCE_DIR}/phphext.i"
  "${PROJECT_SOURCE_DIR}/../wrapper/Html.cpp"
  "${PROJECT_SOURCE_DIR}/../wrapper/Rule.cpp")
swig_link_libraries(phphext hext::hext)
set_target_properties(phphext PROPERTIES OUTPUT_NAME "hext" PREFIX "")

