###### HEXT-RUBY ###############################################################
project(hext-ruby)

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
  cmake_policy(SET CMP0078 NEW)
endif()
if(POLICY CMP0086)
  # https://cmake.org/cmake/help/latest/policy/CMP0086.html
  cmake_policy(SET CMP0086 OLD)
endif()
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

### RUBY
find_package(Ruby REQUIRED)

### LIBHEXT
find_package(Hext REQUIRED)

### WRAPPERS
include_directories("${PROJECT_SOURCE_DIR}/..")


###### RUBY ####################################################################
include_directories(SYSTEM ${RUBY_INCLUDE_DIRS})

set_source_files_properties(
  "${PROJECT_SOURCE_DIR}/rbhext.i" PROPERTIES CPLUSPLUS ON)
swig_add_library(
  rbhext
  LANGUAGE ruby
  SOURCES
  "${PROJECT_SOURCE_DIR}/rbhext.i"
  "${PROJECT_SOURCE_DIR}/../wrapper/Html.cpp"
  "${PROJECT_SOURCE_DIR}/../wrapper/Rule.cpp")
swig_link_libraries(rbhext hext::hext ${RUBY_LIBRARY})
set_target_properties(rbhext PROPERTIES OUTPUT_NAME "hext")

