cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

# https://cmake.org/cmake/help/latest/policy/CMP0167.html
# Prefer Boost-installed cmake configuration for package Boost.
if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

project(libhext-examples)

# Add the top-level cmake module directory to CMAKE_MODULE_PATH
list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/../../cmake)

include(HextEnableWarnings)

find_package(Hext REQUIRED)


add_executable(mixed ${PROJECT_SOURCE_DIR}/mixed.cpp)
hext_enable_warnings(mixed PRIVATE)
target_link_libraries(mixed hext::hext)
target_compile_features(mixed PRIVATE cxx_std_17)


add_executable(chaining-rules ${PROJECT_SOURCE_DIR}/chaining.cpp)
hext_enable_warnings(chaining-rules PRIVATE)
target_link_libraries(chaining-rules hext::hext)
target_compile_features(chaining-rules PRIVATE cxx_std_17)


find_package(PocoFoundation QUIET)
if(${POCOFOUNDATION_FOUND})
  add_executable(extract-href ${PROJECT_SOURCE_DIR}/extract-href.cpp)
  hext_enable_warnings(extract-href PRIVATE)
  target_link_libraries(extract-href ${PocoFoundation_LIBRARY} hext::hext)
  target_compile_features(extract-href PRIVATE cxx_std_17)
  target_include_directories(extract-href PRIVATE ${PocoFoundation_INCLUDE_DIR})
endif()

