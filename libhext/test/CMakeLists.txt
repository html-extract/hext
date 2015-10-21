###### LIBHEXT-TEST ############################################################
PROJECT(libhext-test)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake")

# Force flag -std=c++14.
INCLUDE(HextForceCPP14)

# Enable all (reasonable) warnings with Clang and GCC.
INCLUDE(HextEnableWarnings)


###### DEPENDENCIES ############################################################
# Avoid circular dependency by only loading libhext if it wasn't included
# already.
IF(NOT LIBHEXT_LOADED)
  # Tell libhext that libhext-test is already loaded.
  SET(LIBHEXT_TEST_LOADED "true")
  ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/.." "libhext")
ENDIF(NOT LIBHEXT_LOADED)
# Download and build GoogleTest
INCLUDE(HextExternalProjectGoogleTest)
# GoogleTest requires pthread
FIND_PACKAGE(Threads REQUIRED)


###### INCLUDES ################################################################
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../../libhext/include")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../../libhext/src")


###### SOURCES #################################################################
ADD_EXECUTABLE(
  libhext-test
  "${PROJECT_SOURCE_DIR}/src/main.cpp")
ADD_DEPENDENCIES(libhext-test hext googletest)
IF(THREADS_HAVE_PTHREAD_ARG)
  TARGET_COMPILE_OPTIONS(PUBLIC libhext-test "-pthread")
ENDIF(THREADS_HAVE_PTHREAD_ARG)
TARGET_LINK_LIBRARIES(
  libhext-test
  hext
  gtest
  "${CMAKE_THREAD_LIBS_INIT}")


###### TESTING #################################################################
ENABLE_TESTING()
ADD_TEST("LIBHEXT_GTEST" libhext-test)

