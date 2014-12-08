#### html-extract-test

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)
INCLUDE(ExternalProject) # available since 2.8.7
#SET(CMAKE_VERBOSE_MAKEFILE on)

PROJECT(html-extract-test)

ADD_DEFINITIONS("-std=c++11")
# undefine NDEBUG; this way asserts won't be removed in relase mode
ADD_DEFINITIONS(-UNDEBUG)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")
# add html-extract's src/ directory as an additional include directory
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../src")


###### EXTERNAL DEPENDENCIES ##############################
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/thirdparty)

#
### download and build googletest
ExternalProject_Add(
    googletest
    URL http://googletest.googlecode.com/files/gtest-1.7.0.zip
    TIMEOUT 10

    UPDATE_COMMAND ""
    INSTALL_COMMAND ""

    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# use googletest's include/ directory as an additional include directory
ExternalProject_Get_Property(googletest source_dir)
INCLUDE_DIRECTORIES(${source_dir}/include)

# add googletest's library directory when linking
ExternalProject_Get_Property(googletest binary_dir)
# LINK_DIRECTORIES will apply only to targets created after it is called
LINK_DIRECTORIES(${binary_dir})
###########################################################

# ADD_EXECUTABLE must appear _after_ all calls to LINK_DIRECTORIES
ADD_EXECUTABLE(html-extract-test ${PROJECT_SOURCE_DIR}/src/main.cpp)

# dependency on googletest
ADD_DEPENDENCIES(html-extract-test googletest)
TARGET_LINK_LIBRARIES(html-extract-test gtest)
TARGET_LINK_LIBRARIES(html-extract-test pthread)

###### BUILD OPTIONS ######################################
# enable whole-program optimization on gcc
OPTION(WPO  "Use whole-program optimization on gcc" OFF)
IF(WPO)
  IF(CMAKE_COMPILER_IS_GNUCXX)
    ADD_DEFINITIONS("-fwhole-program")
    SET(CMAKE_EXE_LINKER_FLAGS "-fwhole-program")
  ELSE()
    MESSAGE(STATUS "compiler not g++, cannot use -fwhole-program")
  ENDIF()
ENDIF(WPO)
###########################################################

