###### HTML-EXTRACT-TEST #######################################################
PROJECT(html-extract-test)

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
INCLUDE(HextExternalProjectGoogleTest)


###### INCLUDES ################################################################
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../../libhext/include")


###### SOURCES #################################################################
ADD_EXECUTABLE(
  html-extract-test
  "${PROJECT_SOURCE_DIR}/src/main.cpp")
ADD_DEPENDENCIES(html-extract-test libhext googletest)
TARGET_LINK_LIBRARIES(
  html-extract-test
  hext
  gtest
  pthread)


###### TESTING #################################################################
ENABLE_TESTING()
ADD_TEST("LIBHEXT_GTEST" html-extract-test)


