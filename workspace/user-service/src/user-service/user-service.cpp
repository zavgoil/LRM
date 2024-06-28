#include "user-service/user-service.hpp"

#include "util/log.hpp"

int UserService::run(int argc, char const *argv[]) {
  util::Log::debug("Starting user-service...");

  auto config = getConfig(argc, argv);

  db_manager_ = std::make_shared<DbManager>(config.db_option);

  telegram_notification_producer_ =
      std::make_shared<TelegramNotificationProducer>(
          config.kafka_option.brokers,
          config.kafka_option.telegram_notification_topic);

  grpc_server_ = std::make_unique<UserGrpcServer>(
      config.rpc_map.user_service.uri, config.rpc_map.user_service.port,
      db_manager_, telegram_notification_producer_);

  grpc_server_->wait();
  return 0;
}

// #TODO: добавить возможность указывать конфиги при запуске
Config UserService::getConfig(int argc, char const *argv[]) {
  Config config;
  config.rpc_map.from_yaml_file(RPC_MAP_PATH);
  config.db_option.from_yaml_file(DB_OPTION_PATH);
  config.kafka_option.from_yaml_file(KAFKA_OPTION_PATH);
  return config;
}