cmake_minimum_required(VERSION 3.10)

project(demo-protobuf)

include(FindProtobuf)

add_executable(writeMsg write_message.cxx addressbook.proto)
target_link_libraries(writeMsg protobuf::libprotobuf)
protobuf_generate(TARGET writeMsg)

add_executable(readMsg read_message.cxx addressbook.proto)
target_link_libraries(readMsg protobuf::libprotobuf)
protobuf_generate(TARGET readMsg)

add_executable(readMsgRfl read_message_reflect.cxx addressbook.proto)
target_link_libraries(readMsgRfl protobuf::libprotobuf)
protobuf_generate(TARGET readMsgRfl)

add_executable(writex01 ex01.cxx ex01.proto)
target_link_libraries(writex01 protobuf::libprotobuf)
protobuf_generate(TARGET writex01)

add_executable(writex02 ex02.cxx ex02.proto)
target_link_libraries(writex02 protobuf::libprotobuf)
protobuf_generate(TARGET writex02)

add_executable(writex03 ex03.cxx ex01.proto ex03.proto)
target_link_libraries(writex03 protobuf::libprotobuf)
protobuf_generate(TARGET writex03)
