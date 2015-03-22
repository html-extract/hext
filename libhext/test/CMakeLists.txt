###### LIBHEXT-TEST ############################################################
PROJECT(libhext-test)

# Cmake module ExternalProject is available since 2.8.7.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake")

# Force flag -std=c++11.
INCLUDE(HextForceCPP11)

# Enable all (reasonable) warnings with Clang and GCC.
INCLUDE(HextEnableWarnings)


###### DEPENDENCIES ############################################################
# Avoid circular dependeny by only loading libhext if it wasn't included
# already.
IF(NOT LIBHEXT_LOADED)
  # Tell libhext that libhext-test is already loaded
  SET(LIBHEXT_TEST_LOADED "true")
  ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/.." "libhext")
ENDIF(NOT LIBHEXT_LOADED)
# Download and build GTest.
INCLUDE(HextExternalProjectGoogleTest)


###### INCLUDES ################################################################
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../../libhext/include")


###### SOURCES #################################################################
ADD_EXECUTABLE(
  libhext-test
  "${PROJECT_SOURCE_DIR}/src/main.cpp")
ADD_DEPENDENCIES(libhext-test libhext googletest)
TARGET_LINK_LIBRARIES(
  libhext-test
  hext
  gtest
  pthread)


###### TESTING #################################################################
ENABLE_TESTING()
ADD_TEST("LIBHEXT_GTEST" libhext-test)

