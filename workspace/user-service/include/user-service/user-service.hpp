#pragma once

#include <db/db_manager.h>

#include <config/config.hpp>
#include <memory>
#include <user-service/user-grpc-server.hpp>
class UserService {
 public:
  int run(int argc, char const *argv[]);

 private:
  DbManager db_manager_;
  std::unique_ptr<UserGrpcServer> grpc_server_{nullptr};

  Config getConfig(int argc, char const *argv[]);
};