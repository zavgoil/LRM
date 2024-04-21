#include "user-service/user-service.hpp"

#include "util/log.hpp"

int UserService::run() {
  util::Log::debug("Starting user-service...");
  grpc_server_.wait();
  return 0;
}