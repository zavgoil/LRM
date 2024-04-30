#pragma once

#include <db/db_manager.h>
#include <proto/user-service.grpc.pb.h>

class SignUpService : public user_service::SignUp::Service {
 public:
  SignUpService(DbManager& db);
  ::grpc::Status SignUp(::grpc::ServerContext* context,
                        const ::user_service::SignUpRequest* request,
                        ::user_service::SignUpResponse* response) override;

 private:
  DbManager& db_;
};