#pragma once

#include <db/db_manager.h>
#include <proto/user-service.grpc.pb.h>

#include <memory>

class NotifClientGrpcService
    : public user_service::NotificationClientService::Service {
 public:
  NotifClientGrpcService(std::shared_ptr<DbManager> db);

  ::grpc::Status SetNotificationClients(
      ::grpc::ServerContext* context,
      const ::user_service::SetNotificationClientsRequest* request,
      ::user_service::SetNotificationClientsResponse* response) override;

  ::grpc::Status GetNotificationClients(
      ::grpc::ServerContext* context,
      const ::user_service::GetNotificationClientsRequest* request,
      ::user_service::GetNotificationClientsResponse* response) override;

 private:
  std::shared_ptr<DbManager> db_;
};