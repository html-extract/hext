if(NOT HEXT_VERSION_FILE_SOURCE)
  message(FATAL_ERROR "HEXT_VERSION_FILE_SOURCE not set. Cannot generate version file.")
else(NOT HEXT_VERSION_FILE_SOURCE)
  # Note: GET_FILENAME_COMPONENT cannot be used here, it strips all extensions.
  string(REGEX REPLACE ".in$" "" HEXT_VERSION_FILE_TARGET ${HEXT_VERSION_FILE_SOURCE})

  configure_file(
    ${HEXT_VERSION_FILE_SOURCE}
    ${HEXT_VERSION_FILE_TARGET}
    @ONLY)
endif(NOT HEXT_VERSION_FILE_SOURCE)

