cmake_minimum_required(VERSION 3.22)

project(user-service)
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
target_include_directories(user-service PRIVATE include/)
target_link_libraries(user-service PRIVATE project-util proto pqxx rdkafka++)

target_compile_definitions(user-service PRIVATE 
                           RPC_MAP_PATH="${PROJECT_UTIL_RPC_MAP_PATH}"
                           DB_OPTION_PATH="${CMAKE_CURRENT_SOURCE_DIR}/config/db_option.yaml"
                           KAFKA_OPTION_PATH="${CMAKE_CURRENT_SOURCE_DIR}/config/kafka_option.yaml")