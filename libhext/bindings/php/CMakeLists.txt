###### HEXT-PHP ################################################################
PROJECT(hext-php)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../../cmake")

# Set required C++ standard or abort.
INCLUDE(HextForceCppStd)

# If build type was not specified, build Release.
INCLUDE(HextDefaultBuildRelease)


###### DEPENDENCIES ############################################################

### SWIG
FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

### PHP
FIND_PACKAGE(PHP REQUIRED)

### LIBHEXT
FIND_PACKAGE(Hext REQUIRED)
INCLUDE_DIRECTORIES(${HEXT_INCLUDE_DIR})

### WRAPPERS
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/..")


###### SWIG ####################################################################
SET(CMAKE_SWIG_FLAGS "-c++")


###### PHP #####################################################################
INCLUDE_DIRECTORIES(SYSTEM ${PHP_INCLUDE_DIRS})

SET_SOURCE_FILES_PROPERTIES(
  "${PROJECT_SOURCE_DIR}/phphext.i" PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(
  phphext php
  "${PROJECT_SOURCE_DIR}/phphext.i"
  "${PROJECT_SOURCE_DIR}/../wrapper/Html.cpp"
  "${PROJECT_SOURCE_DIR}/../wrapper/Rule.cpp")
SWIG_LINK_LIBRARIES(phphext ${HEXT_LIBRARY})
SET_TARGET_PROPERTIES(phphext PROPERTIES OUTPUT_NAME "hext" PREFIX "")

