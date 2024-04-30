cmake_minimum_required(VERSION 3.22)

project(project-util)

add_library(project-util INTERFACE)
target_link_libraries(project-util INTERFACE yaml-cpp nlohmann_json::nlohmann_json)
target_include_directories(project-util INTERFACE "include/")