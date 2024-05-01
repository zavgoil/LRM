cmake_minimum_required(VERSION 3.22)

project(user-service)
set(CMAKE_CXX_STANDARD 17)
set(SRC_FILES src/user-service/user-service.cpp
              src/user-service/auth-service.cpp
              src/db/db_manager.cpp
              src/util/log.cpp)


add_executable(user-service src/main.cpp
                            ${SRC_FILES})
target_include_directories(user-service PRIVATE include/)
target_link_libraries(user-service PRIVATE project-util proto pqxx)