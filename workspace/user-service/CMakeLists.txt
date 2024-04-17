cmake_minimum_required(VERSION 3.22)

project(user-service)

set(CMAKE_CXX_STANDARD 17)

set(SRC_FILES src/user-service/user-service.cpp
              src/util/log.cpp)

include_directories(include/)

add_executable(user-service src/main.cpp
                            ${SRC_FILES})