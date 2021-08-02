###### LIBHEXT-TEST ############################################################
project(libhext-test)

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# Add the top-level cmake module directory to CMAKE_MODULE_PATH
list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/../../cmake)

include(HextEnableWarnings)


###### DEPENDENCIES ############################################################
add_subdirectory("${PROJECT_SOURCE_DIR}/.." "libhext")
# libhext-test also depends on the private API which is hidden in the default
# build of libhext.
set_target_properties(hext PROPERTIES CXX_VISIBILITY_PRESET default)
find_package(Gumbo REQUIRED)
find_package(GTest REQUIRED)
# GoogleTest requires pthread
find_package(Threads REQUIRED)


###### INCLUDES ################################################################
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/../../libhext/include")
include_directories("${PROJECT_SOURCE_DIR}/../../libhext/src")
include_directories("${Gumbo_INCLUDE_DIR}")
include_directories("${GTEST_INCLUDE_DIRS}")


###### SOURCES #################################################################
add_executable(
  libhext-test
  "${PROJECT_SOURCE_DIR}/src/builtins/inner-html-builtin.cpp"
  "${PROJECT_SOURCE_DIR}/src/builtins/strip-tags-builtin.cpp"
  "${PROJECT_SOURCE_DIR}/src/builtins/text-builtin.cpp"
  "${PROJECT_SOURCE_DIR}/src/helper/node.cpp"
  "${PROJECT_SOURCE_DIR}/src/html/html.cpp"
  "${PROJECT_SOURCE_DIR}/src/html-tag/html-tag.cpp"
  "${PROJECT_SOURCE_DIR}/src/parse-hext/parse-hext.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/attribute-capture.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/attribute-count-match.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/attribute-match.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/begins-with-test.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/child-count-match.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/contains-test.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/contains-words-test.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/ends-with-test.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/equals-test.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/function-capture.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/function-match.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/function-value-match.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/negate-match.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/negate-test.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/nth-child-match.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/only-child-match.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/regex-test.cpp"
  "${PROJECT_SOURCE_DIR}/src/pipe/append-pipe.cpp"
  "${PROJECT_SOURCE_DIR}/src/pipe/case-pipe.cpp"
  "${PROJECT_SOURCE_DIR}/src/pipe/collapsews-pipe.cpp"
  "${PROJECT_SOURCE_DIR}/src/pipe/prepend-pipe.cpp"
  "${PROJECT_SOURCE_DIR}/src/pipe/regex-pipe.cpp"
  "${PROJECT_SOURCE_DIR}/src/pipe/regex-replace-pipe.cpp"
  "${PROJECT_SOURCE_DIR}/src/pipe/string-pipe.cpp"
  "${PROJECT_SOURCE_DIR}/src/pipe/trim-pipe.cpp"
  "${PROJECT_SOURCE_DIR}/src/rule/rule.cpp"
  "${PROJECT_SOURCE_DIR}/src/rule/rule-matching.cpp"
  "${PROJECT_SOURCE_DIR}/src/string-util/char-position.cpp"
  "${PROJECT_SOURCE_DIR}/src/string-util/is-space.cpp"
  "${PROJECT_SOURCE_DIR}/src/string-util/print-numbered-lines.cpp"
  "${PROJECT_SOURCE_DIR}/src/string-util/trim-and-collapse-ws.cpp"
  "${PROJECT_SOURCE_DIR}/src/main.cpp")
hext_enable_warnings(libhext-test PRIVATE)
if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(PUBLIC libhext-test "-pthread")
endif()
target_link_libraries(
  libhext-test
  hext::hext
  gtest
  "${CMAKE_THREAD_LIBS_INIT}")


###### TESTING #################################################################
enable_testing()
add_test("LIBHEXT_GTEST" libhext-test)

