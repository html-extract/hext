###### HEXT-PYTHON #############################################################
project(hext-python)

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Add the top-level cmake module directory to CMAKE_MODULE_PATH
list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/../../../cmake)

# Set required C++ standard or abort.
include(HextForceCppStd)

# If build type was not specified, build Release.
include(HextDefaultBuildRelease)


###### DEPENDENCIES ############################################################

### SWIG
if(POLICY CMP0078)
  # https://cmake.org/cmake/help/latest/policy/CMP0078.html
  cmake_policy(SET CMP0078 OLD)
endif()
if(POLICY CMP0086)
  # https://cmake.org/cmake/help/latest/policy/CMP0086.html
  cmake_policy(SET CMP0086 OLD)
endif()
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

### PYTHON
find_package(PythonLibs REQUIRED)

### LIBHEXT
find_package(Hext REQUIRED)

### WRAPPERS
include_directories("${PROJECT_SOURCE_DIR}/..")


###### PYTHON ##################################################################
include_directories(SYSTEM ${PYTHON_INCLUDE_PATH})

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

