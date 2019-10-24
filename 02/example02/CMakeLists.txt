set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
  Widgets REQUIRED)

add_executable(widget main.cxx)
target_compile_options(widget PUBLIC -rdynamic)
target_link_libraries(widget ${LDLIBS} Qt5::Widgets)

add_library(wplugin1 SHARED plugin1.cxx)
target_compile_options(wplugin1 PUBLIC -rdynamic)
target_link_libraries(wplugin1 ${LDLIBS} Qt5::Widgets)
