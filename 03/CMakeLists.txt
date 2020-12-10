cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

project(hybrid-widget)

include(packages)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)


find_package(Qt5 5.15.0 EXACT COMPONENTS Widgets CONFIG REQUIRED)

add_library(hybrid-library
  qt-core.cxx
  qt-mainwindow.cxx)

target_link_libraries(hybrid-library
  Python3::Python
  Qt5::Widgets)


find_package(Python3 3.6 COMPONENTS Interpreter Development)

find_package(pybind11 REQUIRED)
include(pybind11Tools)
pybind11_add_module(pyplotter model.cxx)

target_link_libraries(pyplotter
  PRIVATE hybrid-library
  PUBLIC pybind11::pybind11
  PUBLIC Python3::Python
  PRIVATE Qt5::Widgets)


add_executable(hybrid-widget
  main.cxx
  qt-classic-widget.cxx)

target_link_libraries(hybrid-widget
  pybind11::pybind11
  Python3::Python
  Qt5::Widgets)

# set(binding_SRC
#   ${CMAKE_CURRENT_BINARY_DIR}/qt-core_wrapper.cpp)

# set(GENERATOR_EXTRA_FLAGS --generator-set=shiboken
#   --enable-parent-ctor-heuristic
#   --enable-pyside-extensions
#   --enable-return-value-heuristic
#   --use-isnull-as-nb_nonzero)

# macro(make_path varname)
#   # accepts any number of path variables
#   string(REPLACE ";" "${PATH_SEP}" ${varname} "${ARGN}")
# endmacro()

# make_path(pyplotter_include_dirs /home/akrutikov/project/pyside
#   ${CMAKE_CURRENT_SOURCE_DIR}
#   )

# make_path(pyplotter_typesystem_path ${CMAKE_CURRENT_SOURCE_DIR}
#   /home/akrutikov/project/pyside
#   )

# add_custom_command(OUTPUT ${binding_SRC}
#   COMMAND shiboken2 ${GENERATOR_EXTRA_FLAGS}
#   ${CMAKE_CURRENT_SOURCE_DIR}/pyplotter_global.h
#   --include-paths=${testbinding_include_dirs}
#   --typesystem-paths=${pyplotter_typesystem_path}
#   --output-directory=${CMAKE_CURRENT_BINARY_DIR}
#   ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_pyplotter.xml
#   --api-version=${SUPPORTED_QT_VERSION}
#   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#   COMMENT "Running generator for test binding..."
#   )
