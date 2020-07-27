set(CONAN "conan" CACHE STRING "Conan executable")
set(CONAN_PROFILE "default" CACHE STRING "Conan profile")

include(buildtype)
include(conan)

conan_cmake_run(
  PROFILE ${CONAN_PROFILE}
  SETTINGS build_type=${CMAKE_BUILD_TYPE}
  REQUIRES pybind11/2.5.0
  GENERATORS cmake_find_package cmake_paths virtualrunenv
  CONAN_COMMAND ${CONAN})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS)
