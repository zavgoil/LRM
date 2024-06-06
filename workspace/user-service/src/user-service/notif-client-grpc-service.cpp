#include <user-service/notif-client-grpc-service.hpp>
#include "db/db_exception.h"

NotifClientGrpcService::NotifClientGrpcService(std::shared_ptr<DbManager> db)
    : db_(db) {}

::grpc::Status NotifClientGrpcService::SetNotificationClients(
    ::grpc::ServerContext* context,
    const ::user_service::SetNotificationClientsRequest* request,
    ::user_service::SetNotificationClientsResponse* response) {
  try {
    db_->setClients(request->user_token(), request->clients());
  } catch (UserNotFound const& e) {
    return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, "User not found");
  }

  response->set_client_count(static_cast<int>(request->clients().size()));

  return ::grpc::Status(::grpc::StatusCode::OK, "");
}

::grpc::Status NotifClientGrpcService::GetNotificationClients(
    ::grpc::ServerContext* context,
    const ::user_service::GetNotificationClientsRequest* request,
    ::user_service::GetNotificationClientsResponse* response) {

  try {
    db_->getClients(request->user_token(), response->mutable_clients());
  } catch (UserNotFound const& e) {
    return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, "User not found");
  }

  return ::grpc::Status(::grpc::StatusCode::OK, "");
}
