###### HEXT-RUBY ###############################################################
PROJECT(hext-ruby)

CMAKE_MINIMUM_REQUIRED(VERSION 3.8 FATAL_ERROR)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../../cmake")

# Set required C++ standard or abort.
INCLUDE(HextForceCppStd)

# If build type was not specified, build Release.
INCLUDE(HextDefaultBuildRelease)


###### DEPENDENCIES ############################################################

### SWIG
IF(POLICY CMP0078)
  # https://cmake.org/cmake/help/latest/policy/CMP0078.html
  CMAKE_POLICY(SET CMP0078 NEW)
ENDIF(POLICY CMP0078)
FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

### RUBY
FIND_PACKAGE(Ruby REQUIRED)

### LIBHEXT
FIND_PACKAGE(Hext REQUIRED)
INCLUDE_DIRECTORIES(${HEXT_INCLUDE_DIR})

### WRAPPERS
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/..")


###### RUBY ####################################################################
INCLUDE_DIRECTORIES(SYSTEM ${RUBY_INCLUDE_DIRS})

SET_SOURCE_FILES_PROPERTIES(
  "${PROJECT_SOURCE_DIR}/rbhext.i" PROPERTIES CPLUSPLUS ON)
SWIG_ADD_LIBRARY(
  rbhext
  LANGUAGE ruby
  SOURCES
  "${PROJECT_SOURCE_DIR}/rbhext.i"
  "${PROJECT_SOURCE_DIR}/../wrapper/Html.cpp"
  "${PROJECT_SOURCE_DIR}/../wrapper/Rule.cpp")
SWIG_LINK_LIBRARIES(rbhext ${HEXT_LIBRARY} ${RUBY_LIBRARY})
SET_TARGET_PROPERTIES(rbhext PROPERTIES OUTPUT_NAME "hext")

