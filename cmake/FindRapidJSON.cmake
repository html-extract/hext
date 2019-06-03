include(FindPackageHandleStandardArgs)

find_path(RapidJSON_INCLUDE_DIR rapidjson/rapidjson.h)
mark_as_advanced(RapidJSON_INCLUDE_DIR)

find_package_handle_standard_args(RapidJSON
  REQUIRED_VARS RapidJSON_INCLUDE_DIR)

if(RapidJSON_FOUND AND NOT TARGET RapidJSON::RapidJSON)
  add_library(RapidJSON::RapidJSON INTERFACE IMPORTED)
  set_target_properties(RapidJSON::RapidJSON
    PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${RapidJSON_INCLUDE_DIR}")
endif()

