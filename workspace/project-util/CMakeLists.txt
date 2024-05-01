cmake_minimum_required(VERSION 3.22)

project(project-util)

set(PROJECT_UTIL_RPC_MAP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/config/rpc_map.yaml" PARENT_SCOPE)

add_library(project-util INTERFACE)
target_link_libraries(project-util INTERFACE yaml-cpp nlohmann_json::nlohmann_json)
target_include_directories(project-util INTERFACE "include/")