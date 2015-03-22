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
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/.." "libhext")
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

