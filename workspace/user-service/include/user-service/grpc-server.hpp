#pragma once

#include <db/db_manager.h>
#include <grpcpp/grpcpp.h>

#include <user-service/auth-service.hpp>

class GrpcServer {
 public:
  GrpcServer(std::string grpc_uri, int grpc_port, DbManager& db)
      : auth_service_(db) {
    std::string addr = grpc_uri + ":" + std::to_string(grpc_port);
    builder_.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder_.RegisterService(&auth_service_);

    server_ = std::unique_ptr(builder_.BuildAndStart());
  }

  void wait() { server_->Wait(); }

  ~GrpcServer() { server_->Shutdown(); }

 private:
  grpc::ServerBuilder builder_;
  std::unique_ptr<grpc::Server> server_;
  AuthService auth_service_;
};