#pragma once

#include <db/db_manager.h>
#include <proto/user-service.grpc.pb.h>

class AuthGrpcService : public user_service::AuthService::Service {
 public:
  AuthGrpcService(DbManager& db);
  ::grpc::Status SignUp(::grpc::ServerContext* context,
                        const ::user_service::SignUpRequest* request,
                        ::user_service::SignUpResponse* response) override;
  ::grpc::Status SignIn(::grpc::ServerContext* context,
                        const ::user_service::SignInRequest* request,
                        ::user_service::SignInResponse* response) override;

 private:
  DbManager& db_;
};