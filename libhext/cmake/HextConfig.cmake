include(CMakeFindDependencyMacro)
find_dependency(Boost)
find_dependency(Gumbo)
include("${CMAKE_CURRENT_LIST_DIR}/HextTargets.cmake")
