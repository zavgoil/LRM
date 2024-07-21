cmake_minimum_required(VERSION 3.22)
project(proto)

find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set(PROTO_FILES
    proto/user-service.proto)

set(PROTO_PATH ${CMAKE_CURRENT_BINARY_DIR}/include/proto)

add_custom_target(build-time-make-directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROTO_PATH})

add_library(proto ${PROTO_FILES})
add_library(proto::proto ALIAS proto)
target_link_libraries(proto PUBLIC 
    protobuf::libprotobuf 
    gRPC::grpc 
    gRPC::grpc++)
    
protobuf_generate(TARGET proto 
    LANGUAGE cpp
    PROTOC_OUT_DIR ${PROTO_PATH})
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET proto 
    LANGUAGE grpc 
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc 
    PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}"
    PROTOC_OUT_DIR ${PROTO_PATH})

target_include_directories(proto PUBLIC 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/proto>" 
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include/proto>")

install(DIRECTORY 
    ${CMAKE_CURRENT_BINARY_DIR}/include/ 
    DESTINATION 
    include)
install (TARGETS proto EXPORT protoTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
install (EXPORT protoTargets
        NAMESPACE proto::
        DESTINATION lib/cmake/proto
)

install(DIRECTORY 
    ${CMAKE_CURRENT_SOURCE_DIR}/config/ 
    DESTINATION 
    share/project-util/config)


configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/proto-config.cmake
    @ONLY
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/proto-config.cmake
    DESTINATION lib/cmake/proto
)