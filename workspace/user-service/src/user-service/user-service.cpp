#include "user-service/user-service.hpp"

#include "util/log.hpp"

int UserService::run(int argc, char const *argv[]) {
  util::Log::debug("Starting user-service...");

  auto config = getConfig(argc, argv);

  grpc_server_ = std::make_unique<UserGrpcServer>(
      config.rpc_map.user_service.uri, config.rpc_map.user_service.port,
      db_manager_);
  grpc_server_->wait();
  return 0;
}

Config UserService::getConfig(int argc, char const *argv[]) {
  if (argc < 2) throw std::logic_error("args not set");

  Config config;
  std::string rpc_map_path = argv[1];
  config.rpc_map.from_yaml_file(rpc_map_path);

  return config;
}