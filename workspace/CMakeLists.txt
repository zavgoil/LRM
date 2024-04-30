cmake_minimum_required(VERSION 3.22)

project(danger-signal)

add_subdirectory(3rdparty/libpqxx)
add_subdirectory(proto)

add_subdirectory(user-service)
add_subdirectory(gui-client)
