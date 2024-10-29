###### HEXTJS ##################################################################
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

# https://cmake.org/cmake/help/latest/policy/CMP0167.html
# Prefer Boost-installed cmake configuration for package Boost.
if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

project(hextjs)

# Add the top-level cmake module directory to CMAKE_MODULE_PATH
list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/../../../cmake)
# Add hextjs cmake module directory to CMAKE_MODULE_PATH
list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/cmake)

include(HextEnableWarnings)

# If build type was not specified, build Release.
include(HextDefaultBuildRelease)

find_package(Hext REQUIRED)
find_package(NodeAddonApi REQUIRED)

add_library(
  ${PROJECT_NAME} SHARED
  "${PROJECT_SOURCE_DIR}/src/Html.cpp"
  "${PROJECT_SOURCE_DIR}/src/Rule.cpp"
  "${PROJECT_SOURCE_DIR}/src/Hextjs.cpp")

hext_enable_warnings(${PROJECT_NAME} PRIVATE)
set_target_properties(
  ${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node" OUTPUT_NAME "hext")

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_JS_INC}
    ${PROJECT_SOURCE_DIR}/src)

target_compile_definitions(${PROJECT_NAME}
  PRIVATE
  NAPI_VERSION=8)

target_link_libraries(${PROJECT_NAME}
  ${CMAKE_JS_LIB}
  hext::hext
  NodeAddonApi::NodeAddonApi)

option(HEXT_BUILD_STATIC_RELEASE "Build static Hext release" OFF)
if(HEXT_BUILD_STATIC_RELEASE)
  target_link_libraries(
    ${PROJECT_NAME}
    "-static-libgcc"
    "-static-libstdc++"
    "-Wl,--as-needed"
    "-Wl,--exclude-libs,ALL")
endif()

