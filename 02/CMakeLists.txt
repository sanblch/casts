cmake_minimum_required(VERSION 2.6)

project(microplugins CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(microplugins_VERSION_MAJOR 2)
set(microplugins_VERSION_MINOR 0)

# if(WIN32)
#   set(CXXFLAGS -O2 -s -Wall -Wextra)
#   set(LDLIBS -s pthread stdc++fs ole32 oleaut32 psapi advapi32)
# else()
#   set(CXXFLAGS -O1 -s -Wall -Wextra -g -rdynamic)
#   set(LDLIBS -s dl pthread stdc++fs)
# endif()

set(LDFLAGS -rdynamic -fsanitize=address -fsanitize=leak)
set(LDLIBS dl stdc++fs)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/microplugins)

add_subdirectory(example01)
add_subdirectory(example02)
# add_subdirectory(example03)
