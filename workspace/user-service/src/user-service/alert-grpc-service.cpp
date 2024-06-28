#include <db/db_exception.h>

#include <user-service/alert-grpc-service.hpp>

AlertGrpcService::AlertGrpcService(std::shared_ptr<DbManager> db,
                                   std::shared_ptr<TelegramNotificationProducer>
                                       telegram_notification_producer)
    : db_(db),
      telegram_notification_producer_(telegram_notification_producer) {}

::grpc::Status AlertGrpcService::Alert(
    ::grpc::ServerContext* context, const ::user_service::AlertRequest* request,
    ::user_service::AlertResponse* response) {
  ::google::protobuf::RepeatedPtrField<::user_service::NotificationClient>
      clients;

  try {
    db_->getClients(request->user_token(), &clients);
  } catch (UserNotFound const& e) {
    return ::grpc::Status(::grpc::StatusCode::NOT_FOUND, "User not found");
  }

  int count = 0;
  for (auto const& client : clients) {
    switch (client.type()) {
      case ::user_service::NotificationClientType::TELEGRAM:
        count++;
        telegram_notification_producer_->sendMessage(client.data(), "АЛЯРМА");
        break;
      default:
        break;
    }
  }

  response->set_alert_count(count);
  return ::grpc::Status(::grpc::StatusCode::OK, "");
}