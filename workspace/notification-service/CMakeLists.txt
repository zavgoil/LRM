cmake_minimum_required(VERSION 3.22)

project(notification-service)

add_executable(notification-service src/main.cpp)
target_link_libraries(notification-service project-util)
target_include_directories(notification-service PUBLIC "include")