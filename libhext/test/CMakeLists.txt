###### LIBHEXT-TEST ############################################################
PROJECT(libhext-test)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake")

# Force flag -std=c++14.
INCLUDE(HextForceCPP14)

# Enable all (reasonable) warnings with Clang and GCC.
INCLUDE(HextEnableWarnings)


###### DEPENDENCIES ############################################################
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/.." "libhext")
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

# Option SANITIZEADDRESS, default OFF
# Adds -fsanitize=address and -fno-omit-frame-pointer to compiler flags
INCLUDE(HextOptionSanitizeAddress)

# Option SANITIZEUNDEFINED, default OFF
# Adds -fsanitize=undefined and -fno-omit-frame-pointer to compiler flags
INCLUDE(HextOptionSanitizeUndefined)

