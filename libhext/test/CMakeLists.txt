###### LIBHEXT-TEST ############################################################
PROJECT(libhext-test)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake")

# Force flag -std=c++14.
INCLUDE(HextForceCPP14)

# Enable all (reasonable) warnings with Clang and GCC.
INCLUDE(HextEnableWarnings)


###### DEPENDENCIES ############################################################
# Avoid circular dependeny by only loading libhext if it wasn't included
# already.
IF(NOT LIBHEXT_LOADED)
  # Tell libhext that libhext-test is already loaded.
  SET(LIBHEXT_TEST_LOADED "true")
  # Tell libhext not to build swig-hext.
  SET(LIBHEXT_NO_SWIG_HEXT "true")
  ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/.." "libhext")
ENDIF(NOT LIBHEXT_LOADED)
# Download and build GTest (installing GTest is discouraged).
INCLUDE(HextExternalProjectGoogleTest)


###### INCLUDES ################################################################
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../../libhext/include")


###### SOURCES #################################################################
ADD_EXECUTABLE(
  libhext-test
  "${PROJECT_SOURCE_DIR}/src/main.cpp")
ADD_DEPENDENCIES(libhext-test hext googletest)
TARGET_LINK_LIBRARIES(
  libhext-test
  hext
  gtest
  pthread)


###### TESTING #################################################################
ENABLE_TESTING()
ADD_TEST("LIBHEXT_GTEST" libhext-test)


