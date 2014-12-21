#### html-extract

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)
INCLUDE(ExternalProject) # available since 2.8.7
#SET(CMAKE_VERBOSE_MAKEFILE ON)

PROJECT(html-extract)

ADD_DEFINITIONS("-std=c++11")

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")

EXECUTE_PROCESS(COMMAND "${PROJECT_SOURCE_DIR}/scripts/run_ragel.sh" "${PROJECT_SOURCE_DIR}")


###### EXTERNAL DEPENDENCIES ##############################
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/thirdparty)

#
### download and build gumbo
ExternalProject_Add(
    gumbo-parser
    GIT_REPOSITORY https://github.com/google/gumbo-parser.git
    TIMEOUT 10

    CONFIGURE_COMMAND ./autogen.sh && ./configure --prefix=${CMAKE_BINARY_DIR}
    BUILD_COMMAND make
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""

    BUILD_IN_SOURCE ON
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# use gumbo's include/ directory as an additional include directory
ExternalProject_Get_Property(gumbo-parser source_dir)
INCLUDE_DIRECTORIES(${source_dir}/src)

# add gumbo's library directory when linking
ExternalProject_Get_Property(gumbo-parser binary_dir)
# LINK_DIRECTORIES will apply only to targets created after it is called
LINK_DIRECTORIES(${binary_dir}/.libs)
###########################################################

ADD_EXECUTABLE(
  html-extract
  "${PROJECT_SOURCE_DIR}/src/hext/attribute.cpp"
  "${PROJECT_SOURCE_DIR}/src/hext/builtin-captures.cpp"
  "${PROJECT_SOURCE_DIR}/src/main.cpp")
ADD_DEPENDENCIES(html-extract gumbo-parser)
TARGET_LINK_LIBRARIES(html-extract gumbo)

###### WARNINGS ###########################################
# always show warnings
# clang
IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  ADD_DEFINITIONS("-Weverything")
ENDIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

# g++
IF(CMAKE_COMPILER_IS_GNUCXX)
  ADD_DEFINITIONS("-Wconversion" "-Wextra" "-pedantic" "-Wall" "-Wextra"
    "-Wcast-align" "-Wcast-qual" "-Wctor-dtor-privacy"
    "-Wdisabled-optimization" "-Wformat=2" "-Winit-self" "-Wlogical-op"
    "-Wmissing-include-dirs" "-Woverloaded-virtual" "-Wredundant-decls"
    "-Wshadow" "-Wsign-promo" "-Wstrict-null-sentinel" "-Wstrict-overflow=5"
    "-Wundef" "-Wno-unused" "-Weffc++")
  # unused
  # "-Wswitch-default": generated ragel code uses switch without default, 
  #                     we cannot do anything about that
ENDIF(CMAKE_COMPILER_IS_GNUCXX)
###########################################################

###### BUILD OPTIONS ######################################
# force debug symbols (e.g. cmake -DCMAKE_BUILD_TYPE=Release -DSYMBOLS=ON)
OPTION(SYMBOLS "Add debugging symbols" OFF)
IF(SYMBOLS)
  ADD_DEFINITIONS("-g")
ENDIF(SYMBOLS)

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

# gprof build
OPTION(GPROF "gprof build" OFF)
IF(GPROF)
  # -pg must be set when compiling and linking
  ADD_DEFINITIONS("-pg")
  SET(CMAKE_EXE_LINKER_FLAGS "-pg")
ENDIF(GPROF)
###########################################################

