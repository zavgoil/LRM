#pragma once

#include <db/db_manager.h>

#include <user-service/grpc-server.hpp>

class UserService {
 public:
  int run();

 private:
  DbManager db_manager_;
  GrpcServer grpc_server_{db_manager_};
};