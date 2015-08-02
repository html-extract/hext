# Option SANITIZEADDRESS, default OFF
# Adds -fsanitize=address and -fno-omit-frame-pointer to compiler flags

OPTION(SANITIZEADDRESS "add -fsanitize=address and -fno-omit-frame-pointer" OFF)
IF(SANITIZEADDRESS)
  SET(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
  SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
ENDIF(SANITIZEADDRESS)

