# Option SANITIZEUNDEFINED, default OFF
# Adds -fsanitize=undefined and -fno-omit-frame-pointer to compiler flags

OPTION(SANITIZEUNDEFINED "add -fsanitize=undefined and -fno-omit-frame-pointer" OFF)
IF(SANITIZEUNDEFINED)
  SET(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fno-omit-frame-pointer")
  SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")
ENDIF(SANITIZEUNDEFINED)

