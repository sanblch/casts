set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
  Widgets REQUIRED)

add_executable(dynwidget main.cxx)
target_compile_options(dynwidget PUBLIC -rdynamic)
target_link_libraries(dynwidget ${LDLIBS} Qt5::Widgets)
