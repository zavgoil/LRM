// #include <notification-clients/notification-clients.hpp>
#include <user-service/notif-client-grpc-service.hpp>

NotifClientGrpcService::NotifClientGrpcService(std::shared_ptr<DbManager> db)
    : db_(db) {}

::grpc::Status NotifClientGrpcService::SetNotificationClients(
    ::grpc::ServerContext* context,
    const ::user_service::SetNotificationClientsRequest* request,
    ::user_service::SetNotificationClientsResponse* response) {
  NotificationClients clients(request->clients());

  try {
    db_->setClients(request->user_token(), clients);
  } catch (UserNotFound const& e) {
    return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, "User not found");
  }

  response->set_client_count(static_cast<int>(clients.getCount()));

  return ::grpc::Status(::grpc::StatusCode::OK, "");
}

::grpc::Status NotifClientGrpcService::GetNotificationClients(
    ::grpc::ServerContext* context,
    const ::user_service::GetNotificationClientsRequest* request,
    ::user_service::GetNotificationClientsResponse* response) {
    NotificationClients clients{};
  try {
    clients = db_->getClients(request->user_token());
  } catch (UserNotFound const& e) {
    return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, "User not found");
  }

  response->set_allocated_clients(clients.to_proto());

  return ::grpc::Status(::grpc::StatusCode::OK, "");
}