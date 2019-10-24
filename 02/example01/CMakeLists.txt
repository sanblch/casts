add_library(plugin1 SHARED plugin1.cxx)
target_link_options(plugin1 PUBLIC ${LDFLAGS})
target_link_libraries(plugin1 ${LDLIBS})

add_executable(microservice main.cxx)
target_link_options(microservice PUBLIC ${LDFLAGS})
target_link_libraries(microservice ${LDLIBS})
