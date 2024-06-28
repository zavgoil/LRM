#pragma once

#include <db/db_manager.h>

#include <config/config.hpp>
#include <kafka/telegram_notification_producer.hpp>
#include <memory>
#include <user-service/user-grpc-server.hpp>
class UserService {
 public:
  int run(int argc, char const *argv[]);

 private:
  std::shared_ptr<DbManager> db_manager_;
  std::shared_ptr<TelegramNotificationProducer> telegram_notification_producer_;
  std::unique_ptr<UserGrpcServer> grpc_server_{nullptr};

  Config getConfig(int argc, char const *argv[]);
};