#pragma once

#include <db/db_manager.h>
#include <proto/user-service.grpc.pb.h>

#include <memory>

/// @brief gRPC сервис для установки и получения клиентов тревоги
class NotifClientGrpcService
    : public user_service::NotificationClientService::Service {
 public:
  NotifClientGrpcService(std::shared_ptr<DbManager> db);

  /// @brief Установка клиентов тревоги
  /// @param context gRPC контекст
  /// @param request gRPC запрос
  /// @param response gRPC ответ
  /// @return статус
  ::grpc::Status SetNotificationClients(
      ::grpc::ServerContext* context,
      const ::user_service::SetNotificationClientsRequest* request,
      ::user_service::SetNotificationClientsResponse* response) override;

  /// @brief Получение клиентов тревоги
  /// @param context gRPC контекст
  /// @param request gRPC запрос
  /// @param response gRPC ответ
  /// @return статус
  ::grpc::Status GetNotificationClients(
      ::grpc::ServerContext* context,
      const ::user_service::GetNotificationClientsRequest* request,
      ::user_service::GetNotificationClientsResponse* response) override;

 private:
  std::shared_ptr<DbManager> db_;
};