#pragma once

#include <db/db_manager.h>
#include <grpcpp/grpcpp.h>

#include <user-service/sign-in-service.hpp>
#include <user-service/sign-up-service.hpp>

class GrpcServer {
 public:
  GrpcServer(DbManager& db) : sign_in_service_(db), sign_up_service_(db) {
    builder_.AddListeningPort("localhost:50051",
                              grpc::InsecureServerCredentials());
    builder_.RegisterService(&sign_in_service_);
    builder_.RegisterService(&sign_up_service_);

    server_ = std::unique_ptr(builder_.BuildAndStart());
  }

  void wait() { server_->Wait(); }

  ~GrpcServer() { server_->Shutdown(); }

 private:
  grpc::ServerBuilder builder_;
  std::unique_ptr<grpc::Server> server_;
  SignInService sign_in_service_;
  SignUpService sign_up_service_;
};