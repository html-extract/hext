# Option TCMALLOC, default OFF
# Link ${HEXT_LINK_TCMALLOC_TARGET} with libtcmalloc.

IF(NOT HEXT_LINK_TCMALLOC_TARGET)
  # If you hit this error you forgot to set HEXT_LINK_TCMALLOC_TARGET
  # in your CMakeLists.txt. Set it to the name of the target you want to link
  # libtcmalloc with.
  MESSAGE(FATAL_ERROR "HEXT_LINK_TCMALLOC_TARGET not set. Cannot add option TCMALLOC.")
ELSE(NOT HEXT_LINK_TCMALLOC_TARGET)
  OPTION(TCMALLOC "Link with libtcmalloc" OFF)
  IF(TCMALLOC)
    TARGET_LINK_LIBRARIES(${HEXT_LINK_TCMALLOC_TARGET} tcmalloc)

    # -fno-omit-frame-pointer must be set if you configured gperftools with
    # --enable-frame-pointers
    #ADD_DEFINITIONS("-fno-omit-frame-pointer")

    # force gcc to use tcmalloc
    IF(CMAKE_COMPILER_IS_GNUCXX)
      ADD_DEFINITIONS(
        "-fno-builtin-malloc" "-fno-builtin-calloc"
        "-fno-builtin-realloc" "-fno-builtin-free")
    ENDIF(CMAKE_COMPILER_IS_GNUCXX)
  ENDIF(TCMALLOC)
ENDIF(NOT HEXT_LINK_TCMALLOC_TARGET)

