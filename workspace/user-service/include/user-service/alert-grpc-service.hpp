#pragma once

#include <db/db_manager.h>
#include <proto/user-service.grpc.pb.h>

#include <kafka/telegram_notification_producer.hpp>
#include <memory>

/// @brief gRPC сервис для отправки тревоги
class AlertGrpcService : public user_service::AlertService::Service {
 public:
  AlertGrpcService(std::shared_ptr<DbManager> db,
                   std::shared_ptr<TelegramNotificationProducer>
                       telegram_notification_producer);

  /// @brief Отправить тревогу
  /// @param context gGRPC контекст
  /// @param request запрос
  /// @param response ответ
  /// @return статус 
  ::grpc::Status Alert(::grpc::ServerContext* context,
                       const ::user_service::AlertRequest* request,
                       ::user_service::AlertResponse* response) override;

 private:
  std::shared_ptr<DbManager> db_;
  std::shared_ptr<TelegramNotificationProducer> telegram_notification_producer_;
};