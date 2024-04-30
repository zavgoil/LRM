#pragma once

#include <db/db_manager.h>
#include <proto/user-service.grpc.pb.h>

class SignInService : public user_service::SignIn::Service {
 public:
  SignInService(DbManager& db);
  ::grpc::Status SignIn(::grpc::ServerContext* context,
                        const ::user_service::SignInRequest* request,
                        ::user_service::SignInResponse* response) override;

 private:
  DbManager& db_;
};