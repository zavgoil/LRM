cmake_minimum_required(VERSION 3.22)

project(proto)

find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set(PROTO_FILES
    user-service.proto
    notification-service.proto)

set(PROTO_PATH ${CMAKE_CURRENT_BINARY_DIR}/include/proto)

add_custom_target(build-time-make-directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROTO_PATH})

add_library(proto ${PROTO_FILES})
target_link_libraries(proto PUBLIC protobuf::libprotobuf gRPC::grpc gRPC::grpc++)
protobuf_generate(TARGET proto 
    LANGUAGE cpp
    PROTOC_OUT_DIR ${PROTO_PATH})
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET proto 
    LANGUAGE grpc 
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc 
    PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}"
    PROTOC_OUT_DIR ${PROTO_PATH})


target_include_directories(proto PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")