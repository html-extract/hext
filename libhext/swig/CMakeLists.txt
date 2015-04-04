###### SWIG-HEXT ###############################################################
PROJECT(swig-hext)

# Cmake module ExternalProject is available since 2.8.7.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)

SET(SWIG_HEXT_LOADED "true")

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake")

# Force flag -std=c++11.
INCLUDE(HextForceCPP11)

# If build type was not specified, build Release.
INCLUDE(HextDefaultBuildRelease)


###### DEPENDENCIES ############################################################

### SWIG
FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

### PYTHON
FIND_PACKAGE(PythonLibs)

### RUBY
FIND_PACKAGE(Ruby)

### PHP
FIND_PACKAGE(Php)

### LIBHEXT
IF(NOT LIBHEXT_LOADED)
  SET(LIBHEXT_NO_TESTING "true")
  ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/.." "libhext")
ENDIF(NOT LIBHEXT_LOADED)
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/../../libhext/include")


###### SWIG ####################################################################
SET(CMAKE_SWIG_FLAGS "-c++")
SET(CMAKE_SWIG_OUTDIR ${CMAKE_BINARY_DIR}/swig-hext)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/swig-hext)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/swig-hext)


###### PYTHON ##################################################################
IF(PYTHONLIBS_FOUND)
  INCLUDE_DIRECTORIES(SYSTEM ${PYTHON_INCLUDE_PATH})

  # Hide swig's horrible compiler warnings when building release.
  IF(CMAKE_COMPILER_IS_GNUCXX AND (CMAKE_BUILD_TYPE MATCHES Release))
    SET_SOURCE_FILES_PROPERTIES(pyhextPYTHON_wrap.cxx PROPERTIES COMPILE_FLAGS -w)
  ENDIF(CMAKE_COMPILER_IS_GNUCXX AND (CMAKE_BUILD_TYPE MATCHES Release))

  SET_SOURCE_FILES_PROPERTIES(pyhext.i PROPERTIES CPLUSPLUS ON)
  SWIG_ADD_MODULE(pyhext python pyhext.i)
  SWIG_LINK_LIBRARIES(pyhext hext ${PYTHON_LIBRARIES})
ENDIF(PYTHONLIBS_FOUND)


###### RUBY ####################################################################
IF(RUBY_FOUND)
  INCLUDE_DIRECTORIES(SYSTEM ${RUBY_INCLUDE_DIRS})

  # Hide swig's horrible compiler warnings when building release.
  IF(CMAKE_COMPILER_IS_GNUCXX AND (CMAKE_BUILD_TYPE MATCHES Release))
    SET_SOURCE_FILES_PROPERTIES(rbhextRUBY_wrap.cxx PROPERTIES COMPILE_FLAGS -w)
  ENDIF(CMAKE_COMPILER_IS_GNUCXX AND (CMAKE_BUILD_TYPE MATCHES Release))

  SET_SOURCE_FILES_PROPERTIES(rbhext.i PROPERTIES CPLUSPLUS ON)
  SWIG_ADD_MODULE(rbhext ruby rbhext.i)
  SWIG_LINK_LIBRARIES(rbhext hext ${RUBY_LIBRARY})
ENDIF(RUBY_FOUND)


###### PHP #####################################################################
IF(PHP_FOUND)
  INCLUDE_DIRECTORIES(SYSTEM ${PHP_INCLUDE_DIRS})

  # Hide swig's horrible compiler warnings when building release.
  IF(CMAKE_COMPILER_IS_GNUCXX AND (CMAKE_BUILD_TYPE MATCHES Release))
    SET_SOURCE_FILES_PROPERTIES(phphextPHP_wrap.cxx PROPERTIES COMPILE_FLAGS -w)
  ENDIF(CMAKE_COMPILER_IS_GNUCXX AND (CMAKE_BUILD_TYPE MATCHES Release))

  SET_SOURCE_FILES_PROPERTIES(phphext.i PROPERTIES CPLUSPLUS ON)
  SWIG_ADD_MODULE(phphext php phphext.i)
  SWIG_LINK_LIBRARIES(phphext hext)
ENDIF(PHP_FOUND)

