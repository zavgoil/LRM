#pragma once

#include <db/db_manager.h>
#include <grpcpp/grpcpp.h>

#include <user-service/auth-grpc-service.hpp>
#include <user-service/notif-client-grpc-service.hpp>

class UserGrpcServer {
 public:
  UserGrpcServer(const std::string& grpc_uri, const int& grpc_port,
                 std::shared_ptr<DbManager> db)
      : auth_service_(db), notif_service_(db) {
    std::string addr = grpc_uri + ":" + std::to_string(grpc_port);
    builder_.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder_.RegisterService(&auth_service_);
    builder_.RegisterService(&notif_service_);

    server_ = std::unique_ptr(builder_.BuildAndStart());
  }

  void wait() { server_->Wait(); }

  ~UserGrpcServer() { server_->Shutdown(); }

 private:
  grpc::ServerBuilder builder_;
  std::unique_ptr<grpc::Server> server_;
  AuthGrpcService auth_service_;
  NotifClientGrpcService notif_service_;
};