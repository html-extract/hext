include(FindPackageHandleStandardArgs)

find_path(NodeAddonApi_INCLUDE_DIR napi.h
  PATH_SUFFIXES node-addon-api
  HINTS node_modules)
mark_as_advanced(NodeAddonApi_INCLUDE_DIR)

find_package_handle_standard_args(NodeAddonApi
  REQUIRED_VARS NodeAddonApi_INCLUDE_DIR)

if(NodeAddonApi_FOUND AND NOT TARGET NodeAddonApi::NodeAddonApi)
  add_library(NodeAddonApi::NodeAddonApi INTERFACE IMPORTED)
  set_target_properties(NodeAddonApi::NodeAddonApi
    PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${NodeAddonApi_INCLUDE_DIR}")
endif()

