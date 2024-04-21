cmake_minimum_required(VERSION 3.22)

project(danger-signal)

find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_subdirectory(3rdparty/libpqxx)

add_library(proto proto/user-service.proto)
target_link_libraries(proto protobuf::libprotobuf gRPC::grpc gRPC::grpc++)
protobuf_generate(TARGET proto LANGUAGE cpp)
include_directories("$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>")
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET proto 
    LANGUAGE grpc 
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc 
    PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")

add_subdirectory(user-service)
