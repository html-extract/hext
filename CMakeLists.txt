#### html-extract

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)
#INCLUDE(ExternalProject) # available since 2.8.7
#SET(CMAKE_VERBOSE_MAKEFILE on)

PROJECT(html-extract)

ADD_DEFINITIONS("-std=c++11")

ADD_EXECUTABLE(html-extract "${PROJECT_SOURCE_DIR}/src/main.cpp")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")
#TARGET_LINK_LIBRARIES()

EXECUTE_PROCESS(COMMAND "${PROJECT_SOURCE_DIR}/scripts/run_ragel.sh" "${PROJECT_SOURCE_DIR}")

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

