include(FindPackageHandleStandardArgs)

find_path(Gumbo_INCLUDE_DIR gumbo.h)
find_library(Gumbo_LIBRARY NAMES gumbo)

find_package_handle_standard_args(Gumbo REQUIRED_VARS Gumbo_LIBRARY Gumbo_INCLUDE_DIR)

if(Gumbo_FOUND AND NOT TARGET Gumbo::Gumbo)
  add_library(Gumbo::Gumbo UNKNOWN IMPORTED)
  set_target_properties(Gumbo::Gumbo
    PROPERTIES
      IMPORTED_LOCATION "${Gumbo_LIBRARY}"
      INTERFACE_INCLUDE_DIRECTORIES "${Gumbo_INCLUDE_DIR}")
endif()

