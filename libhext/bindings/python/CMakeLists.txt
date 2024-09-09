###### HEXT-PYTHON #############################################################
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

# https://cmake.org/cmake/help/latest/policy/CMP0167.html
# Prefer Boost-installed cmake configuration for package Boost.
if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

project(hext-python)

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

### PYTHON
find_package(Python3 COMPONENTS Development.Module REQUIRED)

### LIBHEXT
find_package(Hext REQUIRED)

### WRAPPERS
include_directories("${PROJECT_SOURCE_DIR}/..")


###### PYTHON ##################################################################
include_directories(SYSTEM ${Python3_INCLUDE_DIRS})

set_source_files_properties(
  "${PROJECT_SOURCE_DIR}/pyhext.i" PROPERTIES CPLUSPLUS ON)
swig_add_library(
  hext
  LANGUAGE python
  SOURCES
  "${PROJECT_SOURCE_DIR}/pyhext.i"
  "${PROJECT_SOURCE_DIR}/../wrapper/Html.cpp"
  "${PROJECT_SOURCE_DIR}/../wrapper/Rule.cpp")
swig_link_libraries(hext hext::hext)

