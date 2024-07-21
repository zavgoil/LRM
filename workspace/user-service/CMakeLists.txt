cmake_minimum_required(VERSION 3.22)
project(user-service)

if(PROJECT_IS_TOP_LEVEL)
    find_package(nlohmann_json REQUIRED)
    find_package(libpqxx REQUIRED)
    find_package(proto REQUIRED)
    find_package(project-util REQUIRED)
else()
    add_library(libpqxx::pqxx ALIAS pqxx)
endif()

set(CMAKE_CXX_STANDARD 17)
set(SRC_FILES src/user-service/user-service.cpp
              src/user-service/auth-grpc-service.cpp
              src/user-service/notif-client-grpc-service.cpp
              src/user-service/alert-grpc-service.cpp
              src/notification-client/notification-client-json.cpp
              src/db/db_manager.cpp
              src/kafka/telegram_notification_producer.cpp
              src/util/log.cpp)

add_executable(user-service src/main.cpp
                            ${SRC_FILES})
target_include_directories(user-service PRIVATE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(user-service PRIVATE 
    project-util::project-util 
    proto::proto 
    libpqxx::pqxx 
    rdkafka++)

install (TARGETS user-service EXPORT user-serviceTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
    )

install(DIRECTORY 
    ${CMAKE_CURRENT_SOURCE_DIR}/config/ 
    DESTINATION 
    share/user-service/config)